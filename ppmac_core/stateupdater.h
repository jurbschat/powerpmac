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
			int32_t idx = from_enum(id);
			if(idx >= static_cast<int32_t>(state.motors.size())) {
				THROW_RUNTIME_ERROR("invalid motor index");
			}
			return state.motors[idx];
		}

		PortInfo GetPortInfo(PortID::TYPE id) const {
			int32_t idx = from_enum(id);
			if(idx >= static_cast<int32_t>(state.ports.size())) {
				THROW_RUNTIME_ERROR("invalid port index");
			}
			return state.ports[idx];
		}

		void UpdateGeneralInfo() {
			// general status
			auto query = query::GeneralGetInfo(stdext::span<GlobalInfo>(&state.global, 1));
			auto result = rs.ChannelWriteRead(query.command);
			if(result) {
				auto parserResult = query.parser(*result);
				Update1D(parserResult, query);
			}
		}

		void UpdateMotorOther() {
			// motor status
			auto query = query::MotorGetOtherRange(stdext::make_span(state.motors),
					static_cast<MotorID::TYPE>(0),
					static_cast<MotorID::TYPE>(state.global.maxMotors - 1));
			auto result = rs.ChannelWriteRead(query.command);
			if(result) {
				auto parserResult = query.parser(*result);
				Update1D(parserResult, query);
			}
		}

		void UpdateMotorValues() {
			// motor status
			auto motorQuery = query::MotorGetPositionRange(stdext::make_span(state.motors),
					static_cast<MotorID::TYPE>(0),
					static_cast<MotorID::TYPE>(state.global.maxMotors - 1));
			auto motorResult = rs.ChannelWriteRead(motorQuery.command);
			if(motorResult) {
				auto parserResult = motorQuery.parser(*motorResult);
				Update2D(parserResult, motorQuery);
			}
		}

		void UpdateMotorStates() {
			auto query = query::MotorGetStatusRange(stdext::make_span(state.motors),
					static_cast<MotorID::TYPE>(0),
					static_cast<MotorID::TYPE>(state.global.maxMotors - 1));
			auto result = rs.ChannelWriteRead(query.command);
			if(result) {
				auto parserResult = query.parser(*result);
				Update1D(parserResult, query);
			}

			// we need to check if we got into an error state
		}

		template<typename T, typename U>
		/*
		 * needs parser results in the form of (1 to x lines with 1.x values in each line)
		 * [0] 0 0 0 0 0 0 0 0
		 * [1] 1 2 3 4 5 6 7 8
		 * ...
		 * each line corresponds to an actual attribute in the specified
		 * struct (through a member pointer). each value will be mapped
		 * to an array index that is defined by the query range in the
		 * querybuilder.
		 */
		void Update2D(const T &parseResult, const U &query) {
			// check if we have as many member pointers as we have result lines
			if(std::tuple_size<decltype(query.pointers.memberPointer)>::value != parseResult.size()) {
				THROW_RUNTIME_ERROR("unable to match parsed data to internal state, size mismatch state:{} != result:{}",
						std::tuple_size<decltype(query.pointers.memberPointer)>::value,
						parseResult.size());
			}
			// we iterate over each member pointer in the queries tuple and match those
			// to the actual structs that we want to update
			for_each_in_tuple(query.pointers.memberPointer, [&parseResult, &query](auto target, size_t tupleIndex)
			{
				auto& lineResultVector = parseResult[tupleIndex];
				if(lineResultVector.size() + query.rangeStart > static_cast<size_t>(query.pointers.data.size())) {
					THROW_RUNTIME_ERROR("result to large {} > {}, unable to update target range",
							lineResultVector.size() + query.rangeStart,
							query.pointers.data.size());
				}
				// first we get the parsed result for the first index
				// then we take each object and apply the current value
				// to the sturcts member pointer e.g.:
				// for each member in list (MotorInfo::position, MotorInfo::velocity)
				//     for each motor in motors
				//         motor.<either position or velocity> = value
				for(size_t i = 0; i < lineResultVector.size(); i++) {
					auto value = lineResultVector[i]; // decltype(getPointerType(target))
					size_t offset = query.rangeStart + i;
					// check if the offset of our line result fits into the size of the actual
					// objects we hold as state
					/*if(offset > static_cast<size_t>(query.pointers.data.size())) {
						THROW_RUNTIME_ERROR("data offset for value update is out of range size:{}, offset:{}",
								query.pointers.data.size(),
								offset);
					}*/
					// explicitly cast, we assume this is possible. if not there is s mismatch between parser type and specified struct types
					(query.pointers.data.data() + offset)->*target = value;
				}
			});
		}

		template<typename T, typename U>
		/*
		 * need parser results in the form of
		 * [0] value1 <- start of object
		 * [1] value2
		 * [..] ...
		 * [5] value1 <- start of next object
		 * [6] value2
		 * ... (many more but always in the same order)
		 * where each X items (denoted as the member pointers in the query)
		 * belong to one object, size % pointerCount yields the result size
		 */
		void Update1D(const T &parseResult, const U &query)
		{
			constexpr size_t packSize = std::tuple_size<decltype(query.pointers.memberPointer)>::value;
			if(parseResult.size() % packSize != 0) {
				THROW_RUNTIME_ERROR("unable to match data to query, {} is not a multiple of {}",
						parseResult.size(),
						packSize);
			}
			size_t outputSize = static_cast<size_t>(query.pointers.data.size());
			if((parseResult.size() / packSize) + query.rangeStart > outputSize) {
				THROW_RUNTIME_ERROR("resul to large {} > {}, unable to update target range",
						(parseResult.size() / packSize) + query.rangeStart,
						query.pointers.data.size());

			}
			// this is the amount of objects we need to iterate about. the objValueStartIndex always points to the
			// first value in the parsers result that starts a new object
			size_t objectsInResult = parseResult.size() / packSize;
			for(size_t objectIndex = 0; objectIndex < objectsInResult; objectIndex++)
			{
				for_each_in_tuple(query.pointers.memberPointer, [&](auto target, size_t tupleIndex) {
					size_t valueOffset = (objectIndex * packSize) + tupleIndex;
					size_t objectOffset = objectIndex + query.rangeStart;
					auto& value = parseResult[valueOffset];
					(query.pointers.data.data() + objectOffset)->*target = value;
				});
			}
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
				UpdateMotorValues();
			}});

			timeout.AddTimer(UpdateTime{std::chrono::milliseconds{1}, [&, this](){
				_1msUpdates++;
				UpdateMotorStates();
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
