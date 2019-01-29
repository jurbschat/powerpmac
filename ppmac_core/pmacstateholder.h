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
				UpdateStateFromQueryResult(parseResult, generalQuery);
			}
		}

		void UpdateMotorValues() {
			// motor status
			auto motorQuery = query::MotorGetPositionRange(stdext::make_span(state.motors),
					static_cast<MotorID::TYPE>(0),
					static_cast<MotorID::TYPE>(state.global.maxMotors));
			auto motorResult = rs.ChannelWriteRead(motorQuery.command);
			if(motorResult) {
				auto parseResult = parser::ParseMultilineResult<parser::FloatParser>(*motorResult);
				UpdateStateFromQueryResult(parseResult, motorQuery);
			}
		}

		void UpdateMotorStates() {
			auto stateQuery = query::MotorGetStatusRange(stdext::make_span(state.motors), MotorID::Motor0, MotorID::Motor8);
			auto stateResult = rs.ChannelWriteRead(stateQuery.command);
			if(stateResult) {
				auto parseResult = parser::ParseMultilineResult<parser::Hex64Parser >(*stateResult);
				UpdateStateFromQueryResult(parseResult, stateQuery);
			}
		}


		template<typename T, typename U>
		void UpdateStateFromQueryResult(const T &parseResult, const U &query) {
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

	private:
		void UpdateEverySecond() {
			// global status
			UpdateGeneralInfo();
		}
		void UpdateEvery100MS() {}
		void UpdateEvery10MS() {
			// motor status
			// motor positions (pos,
		}
		void UpdateAlways() {
			//UpdateMotorValues();
			UpdateMotorStates();
		}

		void QueryPPmacState() {
			StopWatch sw{true};
			int32_t updates = 0;
			running = true;
			UpdateGeneralInfo();
			while(shouldUpdate) {
				if(rs.IsConnected()) {
					try {
						//UpdateEverySecond();
						UpdateEvery100MS();
						UpdateEvery10MS();
						UpdateAlways();
						updates++;
					} catch(const RuntimeError& e) {
						SPDLOG_ERROR("unable to update states:\n{}", StringifyException(std::current_exception(), 4, '>'));
					}
					//std::this_thread::sleep_for(std::chrono::milliseconds{10});
					if(sw.elapsed() > std::chrono::seconds{1}) {
						SPDLOG_DEBUG("updates {} times", updates);
						updates = 0;
						sw.restart();
					}
				} else {
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
