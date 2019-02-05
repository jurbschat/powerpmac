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
#include "pmac/enumadapt.h"
#include "stopwatch.h"

#include <spdlog/spdlog.h>

#include <vector>
#include <cstdint>
#include <thread>

namespace ppmac {

	class StateUpdater
	{
	public:
		StateUpdater(CoreNotifyInterface& core, RemoteShell& rs)
			: core(core),
			rs(rs),
			shouldUpdate(true),
			running(false)
		{
			state.motors.resize(MAX_MOTORS);
			state.ios.resize(MAX_PORTS);
		}

		~StateUpdater() {
			Stop();
		}

		void Start() {
			if(running) {
				return;
			}
			shouldUpdate = true;
			running = true; // we want to instantly be in the "running mode", even if the thread needs some time to start
			updateThread = std::thread([this](){
				QueryPPmacState();
			});
		}

		void Stop() {
			if(!running) {
				return;
			}
			shouldUpdate = false;
			if (updateThread.joinable()) {
				updateThread.join();
			}
		}

		MotorInfo GetMotorInfo(MotorID id) const {
			int32_t idx = from_enum(id);
			if(idx >= static_cast<int32_t>(state.motors.size())) {
				THROW_RUNTIME_ERROR("invalid motor id {}, valid: [{}, {}]", from_enum(id), 0, state.motors.size());
			}
			return state.motors[idx];
		}

		IOInfo GetIoInfo(IoID id) const {
			int32_t idx = from_enum(id);
			if(idx >= static_cast<int32_t>(state.ios.size())) {
				THROW_RUNTIME_ERROR("invalid IO id {}, valid: [{}, {}]", from_enum(id), 0, state.ios.size());
			}
			return state.ios[idx];
		}

		CoordInfo GetCoordInfo(CoordID id) const {
			int32_t idx = from_enum(id);
			if(idx >= static_cast<int32_t>(state.coords.size())) {
				THROW_RUNTIME_ERROR("invalid coord id {}, valid: [{}, {}]", from_enum(id), 0, state.coords.size());
			}
			return state.coords[idx];
		}

		GlobalInfo GetGlobalInfo() const {
			return state.global;
		}

		void UpdateGeneralInfo() {
			std::lock_guard<std::mutex> lock(stateMutex);
			// general status
			auto query = query::GeneralGetInfo(stdext::span<GlobalInfo>(&state.global, 1));
			auto result = rs.ChannelWriteRead(query.command);
			if(result) {
				auto parserResult = query.parser(*result);
				Update1D(parserResult, query);
			}
		}

		void UpdateMotorOther() {
			std::lock_guard<std::mutex> lock(stateMutex);
			// motor status
			auto query = query::MotorGetOtherRange(stdext::make_span(state.motors), 0, state.global.maxMotors - 1);
			auto result = rs.ChannelWriteRead(query.command);
			if(result) {
				auto parserResult = query.parser(*result);
				Update1D(parserResult, query);
			}
		}

		void UpdateMotorValues() {
			std::lock_guard<std::mutex> lock(stateMutex);
			// motor status
			auto motorQuery = query::MotorGetPositionRange(stdext::make_span(state.motors), 0, state.global.maxMotors - 1);
			auto motorResult = rs.ChannelWriteRead(motorQuery.command);
			if(motorResult) {
				auto parserResult = motorQuery.parser(*motorResult);
				Update2D(parserResult, motorQuery);
			}
		}

		void UpdateMotorStatus() {
			std::lock_guard<std::mutex> lock(stateMutex);
			auto query = query::MotorGetStatusRange(stdext::make_span(state.motors), 0, state.global.maxMotors - 1);
			auto result = rs.ChannelWriteRead(query.command);
			if(result) {
				auto parserResult = query.parser(*result);
				Update1D(parserResult, query);
				CheckForMotorStateChanges();
			}
		}

		void CheckForMotorStateChanges() {
			//std::lock_guard<std::mutex> lock(stateMutex);
			for(size_t i = 0; i < state.motors.size(); i++) {
				auto& m = state.motors[i];
				if(m.status.registerValue != m.prevStatus.registerValue) {
					uint64_t changes = m.prevStatus.registerValue ^ m.status.registerValue;
					core.OnMotorStateChanged(i, m.status.registerValue, changes);
					//PrintStateChanges(i, m.prevStatus.registerValue, m.status.registerValue);
					m.prevStatus = m.status;
				}
			}
		}

		void PrintStateChanges(size_t motor, uint64_t was, uint64_t is) {
			fmt::print("MOTOR: {}\n", motor);
			fmt::print("old {:B}\n", was);
			fmt::print("new {:B}\n", is);
			for(int i = 0; i < 64; i++) {
				bool a = bits::isSet(was, i);
				bool b = bits::isSet(is, i);
				if(a != b) {
					auto name = wise_enum::to_string(static_cast<MotorStatusBits::TYPE>(i));
					fmt::print("{} changed {}->{}\n", name, a, b);
				}
			}
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
			StopWatch<> sw{true};
			int32_t _1sUpdates = 0;
			int32_t _100msUpdates= 0;
			int32_t _10msUpdates = 0;
			int32_t _1msUpdates = 0;

			IntervalTimer timeout{0.07f};

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
				UpdateMotorStatus();
			}});

			while(shouldUpdate) {
				if(rs.IsConnected()) {
					try {
						if(state.global.maxMotors == 0) {
							UpdateGeneralInfo();
							std::this_thread::sleep_for(std::chrono::seconds{1});
							continue;
						}
						StopWatch<> sleepTimer{true};
						timeout.Update();
						auto timeLeft =  (timeout.GetMinInterval() - sleepTimer.Elapsed()) / 2;
						if(timeLeft > time::zero) {
							//std::this_thread::sleep_for(timeLeft);
						} else {
							//SPDLOG_DEBUG("no time left, unable to sleep");
						}
						// test stuff
						if(sw.Elapsed() >= std::chrono::seconds{3}) {
							SPDLOG_DEBUG("update stats ({}s): [1s:{}, 100ms:{}, 10ms:{}, 1ms:{}]",
									StopWatch<>::ToDouble(sw.Elapsed()),
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
						SPDLOG_ERROR("exception while updating states:\n{}", StringifyException(std::current_exception(), 4, '>'));
					}
				} else {
					SPDLOG_DEBUG("state holder waiting for connection...");
					std::this_thread::sleep_for(std::chrono::seconds{1});
				}
			}
			running = false;
		}

		CoreNotifyInterface& core;
		RemoteShell& rs;
		bool shouldUpdate;
		bool running;
		std::thread updateThread;
		struct PmacData {
			std::vector<MotorInfo> motors;
			std::vector<IOInfo> ios;
			std::vector<CoordInfo> coords;
			GlobalInfo global;
		} state;
		std::mutex stateMutex;
	};

}

#endif //POWERPMAC_INTERNALSTATE_H
