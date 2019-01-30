//
// Created by urbschaj on 14.01.19.
//

#ifndef POWERPMAC_INTERNALSTATE_H
#define POWERPMAC_INTERNALSTATE_H

#include "remoteshell.h"
#include "throw.h"
#include "commandbuilder.h"
#include "commandquery.h"
#include "resultparser.h"
#include "utility.h"
#include "intervaltimer.h"
#include "pmac/defines.h"
#include "pmac/datastructures.h"
#include "stopwatch.h"

#include <spdlog/spdlog.h>

#include <vector>
#include <cstdint>
#include <thread>

namespace ppmac {

	class PmacStateHolder
	{
	public:
		PmacStateHolder(RemoteShell& rs)
			: rs(rs),
			shouldUpdate(true),
			running(false)
		{
			state.motors.resize(MAX_MOTORS);
			state.ports.resize(MAX_PORTS);
			//TODO: get initial stuff e.g. max motors/coords
		}

		~PmacStateHolder() {
			Stop();
		}

		void Start() {
			if(running) {
				return;
			}
			shouldUpdate = true;
			updateThread = std::thread([this](){
				QueryPPmacState();
			});
		}

		void Stop() {
			if(!running) {
				return;
			}
			shouldUpdate = false;
			if(updateThread.joinable()) {
				updateThread.join();
			}
		}

		MotorInfo GetMotorInfo(MotorID::TYPE id) const {
			int32_t idx = convert::from_enum(id);
			if(idx >= static_cast<int32_t>(state.motors.size())) {
				THROW_RUNTIME_ERROR("invalid motor index");
			}
			return state.motors[idx];
		}

		PortInfo GetPortInfo(PortID::TYPE id) const {
			int32_t idx = convert::from_enum(id);
			if(idx >= static_cast<int32_t>(state.ports.size())) {
				THROW_RUNTIME_ERROR("invalid port index");
			}
			return state.ports[idx];
		}

		void UpdateAllState() {
			UpdateGeneralInfo();
			UpdateMotorValues();
			UpdateMotorStates();
		}

		void UpdateGeneralInfo() {
			// general status
			auto generalQuery = query::GeneralGetInfo(stdext::span<GlobalInfo>(&state.global, static_cast<ptrdiff_t>(0)));
			auto generalResult = rs.ChannelWriteRead(generalQuery.command);
			if(generalResult) {
				auto parseResult = parser::ParseMultilineResult<parser::FloatParser>(*generalResult);
				UpdateFromLineResult(parseResult, generalQuery);
			}
		}

		void UpdateMotorOther() {
			// motor status
			auto motorQuery = query::MotorGetOtherRange(stdext::make_span(state.motors),
					static_cast<MotorID::TYPE>(0),
					static_cast<MotorID::TYPE>(state.global.maxMotors - 1));
			auto motorResult = rs.ChannelWriteRead(motorQuery.command);
			if(motorResult) {
				auto parseResult = parser::ParseMultilineResult<parser::FloatParser>(*motorResult);
				UpdateFromLineResult(parseResult, motorQuery);
			}
		}

		void UpdateMotorValues() {
			// motor status
			auto motorQuery = query::MotorGetPositionRange(stdext::make_span(state.motors),
					static_cast<MotorID::TYPE>(0),
					static_cast<MotorID::TYPE>(state.global.maxMotors - 1));
			auto motorResult = rs.ChannelWriteRead(motorQuery.command);
			if(motorResult) {
				auto parseResult = parser::ParseMultilineResult<parser::FloatParser>(*motorResult);
				UpdateFromLineResult(parseResult, motorQuery);
			}
		}

		void UpdateMotorStates() {
			auto stateQuery = query::MotorGetStatusRange(stdext::make_span(state.motors),
					static_cast<MotorID::TYPE>(0),
					static_cast<MotorID::TYPE>(state.global.maxMotors - 1));
			auto stateResult = rs.ChannelWriteRead(stateQuery.command);
			if(stateResult) {
				auto parseResult = parser::ParseMultilineResult<parser::Hex64Parser >(*stateResult);
				UpdateFromLineResult(parseResult, stateQuery);
			}
		}

		template<typename T, typename U>
		/*
		 * needs parser results in the form of (1 to x lines)
		 * 0 0 0 0 0 0 0 0
		 * 1 2 3 4 5 6 7 8
		 * .....
		 * each line corresponds to an actual attribute in the specified
		 * struct (through a member pointer). each value will be mapped
		 * to an array index that is defined by the query range in the
		 * querybuilder.
		 */
		void UpdateFromLineResult(const T &parseResult, const U &query) {
			// check if we have as many member pointers as we have result lines
			if(std::tuple_size<decltype(query.pointers.memberPointer)>::value != parseResult.size()) {
				THROW_RUNTIME_ERROR("unable to match parsed data to internal state, size mismatch state:{} != result:{}",
						std::tuple_size<decltype(query.pointers.memberPointer)>::value,
						parseResult.size());
			}
			// we iterate over each member pointer in the queries tuple and match those
			// to the actual structs that we want to update
			for_each_in_tuple(query.pointers.memberPointer, [&parseResult, &query](auto target, size_t tupleIndex) {
				// first we get the parsed result for the first index
				// then we take each object and apply the current value
				// to the sturcts member pointer e.g.:
				// for each member in list (MotorInfo::position, MotorInfo::velocity)
				//     for each motor in motors
				//         motor.<either position or velocity> = value
				auto& lineResultVector = parseResult[tupleIndex];
				for(size_t i = 0; i < lineResultVector.size(); i++) {
					auto value = lineResultVector[i]; // decltype(getPointerType(target))
					size_t offset = query.rangeStart + i;
					// check if the offset of our line result fits into the size of the actual
					// objects we hold as state
					if(offset > static_cast<size_t>(query.pointers.data.size())) {
						THROW_RUNTIME_ERROR("data offset for value update is out of range size:{}, offset:{}",
								query.pointers.data.size(),
								offset);
					}
					// explicitly cast, we assume this is possible. if not there is s mismatch between parser type and specified struct types
					(query.pointers.data.data() + offset)->*target = value;
				}
			});
		}

		template<typename T, typename U>
		void UpdateFromRowResult(const T &parseResult, const U &query)
		{
			//
			for(size_t i = 0; i < parseResult.size(); i++)
			{
				auto& line = parseResult[i];
				// we expect there to be only one result,
				if(std::tuple_size<decltype(query.pointers.memberPointer)>::value != line.size()) {
					THROW_RUNTIME_ERROR("unable to match parsed data to internal state, size mismatch state:{} != result:{}",
							std::tuple_size<decltype(query.pointers.memberPointer)>::value,
							parseResult.size());
				}

				//tuple_switch(i, 0, print);
			}

			// we iterate over each member pointer in the queries tuple and match those
			// to the actual structs that we want to update
			for_each_in_tuple(query.pointers.memberPointer, [&parseResult, &query](auto target, size_t tupleIndex) {
				// first we get the parsed result for the first index
				// then we take each object and apply the current value
				// to the sturcts member pointer e.g.:
				// for each member in list (MotorInfo::position, MotorInfo::velocity)
				//     for each motor in motors
				//         motor.<either position or velocity> = value
				auto& lineResultVector = parseResult[tupleIndex];

					size_t offset = query.rangeStart + i;
					// check if the offset of our line result fits into the size of the actual
					// objects we hold as state
					if(offset > static_cast<size_t>(query.pointers.data.size())) {
						THROW_RUNTIME_ERROR("data offset for value update is out of range size:{}, offset:{}",
								query.pointers.data.size(),
								offset);
					}
					// explicitly cast, we assume this is possible. if not there is s mismatch between parser type and specified struct types
					(query.pointers.data.data() + offset)->*target = value;
				}
			});
		}

	private:
		void QueryPPmacState() {

			// test stuff
			StopWatch sw{true};
			int32_t _1sUpdates = 0;
			int32_t _100msUpdates= 0;
			int32_t _10msUpdates = 0;
			int32_t _1msUpdates = 0;

			IntervalTimer timeout;

			timeout.AddTimer(UpdateTime{std::chrono::milliseconds{1000}, [&, this](){
				_1sUpdates++;
				UpdateGeneralInfo();
				UpdateMotorOther();
			}});

			timeout.AddTimer(UpdateTime{std::chrono::milliseconds{100}, [&, this](){
				(void)this;
				_100msUpdates++;
			}});

			timeout.AddTimer(UpdateTime{std::chrono::milliseconds{10}, [&, this](){
				(void)this;
				_10msUpdates++;
			}});

			timeout.AddTimer(UpdateTime{std::chrono::milliseconds{1}, [&, this](){
				_1msUpdates++;
				UpdateMotorStates();
				UpdateMotorValues();
			}});

			running = true;
			while(shouldUpdate) {
				if(rs.IsConnected()) {
					try {
						StopWatch sleepTimer{true};
						timeout.Update();
						auto timeLeft =  (timeout.GetMinInterval() - sleepTimer.Elapsed()) / 2;
						if(timeLeft > time::zero) {
							std::this_thread::sleep_for(timeLeft);
						} else {
							//SPDLOG_DEBUG("no time left, unable to sleep");
						}
						// test stuff
						if(sw.Elapsed() >= std::chrono::seconds{1}) {
							SPDLOG_DEBUG("update stats ({}s): [1s:{}, 100ms:{}, 10ms:{}, 1ms:{}]",
									sw.Elapsed<double>(),
									_1sUpdates,
									_100msUpdates,
									_10msUpdates,
									_1msUpdates);
							_1sUpdates = 0;
							_100msUpdates= 0;
							_10msUpdates = 0;
							_1msUpdates = 0;
							sw.Restart();
						}
						//std::this_thread::sleep_for(std::chrono::seconds{1});
					}catch(const RuntimeError& e) {
						SPDLOG_ERROR("unable to update states:\n{}", StringifyException(std::current_exception(), 4, '>'));
					}
				} else {
					SPDLOG_DEBUG("state holder waiting for connection...");
					std::this_thread::sleep_for(std::chrono::seconds{1});
				}
			}
			running = false;
		}



		RemoteShell& rs;
		bool shouldUpdate;
		bool running;
		std::thread updateThread;
		struct PmacData {
			std::vector<MotorInfo> motors;
			std::vector<PortInfo> ports;
			GlobalInfo global;
		} state;
	};

}

#endif //POWERPMAC_INTERNALSTATE_H
