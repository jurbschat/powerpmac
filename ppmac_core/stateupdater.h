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
#include <mutex>
#include <condition_variable>
#include <boost/container/flat_set.hpp>

namespace ppmac {

	class StateUpdater
	{
	private:
		using time_point = std::chrono::high_resolution_clock::time_point;
		using clock = std::chrono::high_resolution_clock;

		enum class DataRequestType {
			Global,
			Motor,
			Coord,
			IO
		};

		struct DataRequestInfo {
			time_point lastRequest;
			time_point lastUpdate;
			std::chrono::microseconds updateInterval;
			HandleType timerHandle;
		};

		class SpinLock {
			std::atomic_flag locked = ATOMIC_FLAG_INIT ;
		public:
			void lock() {
				while (locked.test_and_set(std::memory_order_acquire)) { ; }
			}
			void unlock() {
				locked.clear(std::memory_order_release);
			}
		};

		class TicketSpinLock
		{
		public:
			void lock()
			{
				const auto myTicketNo = NextTicketNo.fetch_add(1, std::memory_order_relaxed);

				while (ServingTicketNo.load(std::memory_order_acquire) != myTicketNo) {
					__asm__ ( "pause;" );
				}
			}

			void unlock()
			{
				// We can get around a more expensive read-modify-write operation
				// (std::atomic_size_t::fetch_add()), because no one can modify
				// ServingTicketNo while we're in the critical section.
				const auto newNo = ServingTicketNo.load(std::memory_order_relaxed)+1;
				ServingTicketNo.store(newNo, std::memory_order_release);
			}

		private:
			std::atomic_size_t ServingTicketNo = {0};
			std::atomic_size_t NextTicketNo = {0};
		};

		class FairDualMutex : public std::mutex {
		public:
			void lock() {
				_fairness_mutex.lock();
				std::mutex::lock();
				_fairness_mutex.unlock();
			}
		private:
			std::mutex _fairness_mutex;
		};

	public:
		StateUpdater(CoreNotifyInterface& core, RemoteShell& rs)
			: core(core),
			rs(rs),
			shouldUpdate(true),
			running(false),
			updateShouldBlock(false),
			isUpdateBlocking(false)
		{
			state.motors.resize(MAX_MOTORS);
			state.ios.resize(MAX_PORTS);
			state.global.plcs.resize(MAX_PLC);

			lastRequestTimes[DataRequestType::Global] = DataRequestInfo{ time_point{}, time_point{}, std::chrono::milliseconds{1000},   INVALID_HANDLE };
			lastRequestTimes[DataRequestType::Motor] =  DataRequestInfo{ time_point{}, time_point{}, std::chrono::milliseconds{100},    INVALID_HANDLE };
			lastRequestTimes[DataRequestType::Coord] =  DataRequestInfo{ time_point{}, time_point{}, std::chrono::milliseconds{100},    INVALID_HANDLE };
			lastRequestTimes[DataRequestType::IO] =     DataRequestInfo{ time_point{}, time_point{}, std::chrono::milliseconds{100},    INVALID_HANDLE };
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
				RunRemoteUpdateTimer();
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

		MotorInfo GetMotorInfo(MotorID id) {
			int32_t idx = from_enum(id);
			if(idx >= static_cast<int32_t>(state.motors.size())) {
				THROW_RUNTIME_ERROR("invalid motor id {}, valid: [{}, {}]", from_enum(id), 0, state.motors.size());
			}
			//UpdateIfElapsed(DataRequestType::Motor);
			CreateUpdateTimer(DataRequestType::Motor);
			return state.motors[idx];
		}

		IOInfo GetIoInfo(IoID id) {
			int32_t idx = from_enum(id);
			if(idx >= static_cast<int32_t>(state.ios.size())) {
				THROW_RUNTIME_ERROR("invalid IO id {}, valid: [{}, {}]", from_enum(id), 0, state.ios.size());
			}
			//UpdateIfElapsed(DataRequestType::IO);
			CreateUpdateTimer(DataRequestType::IO);
			return state.ios[idx];
		}

		CoordInfo GetCoordInfo(CoordID id) {
			int32_t idx = from_enum(id);
			if(idx >= static_cast<int32_t>(state.coords.size())) {
				THROW_RUNTIME_ERROR("invalid coord id {}, valid: [{}, {}]", from_enum(id), 0, state.coords.size());
			}
			CreateUpdateTimer(DataRequestType::Coord);
			return state.coords[idx];
		}

		GlobalInfo GetGlobalInfo() {
			CreateUpdateTimer(DataRequestType::Global);
			return state.global;
		}

	private:
		void UpdateGeneralInfo() {
			std::lock_guard<std::mutex> lock(stateMutex);
			SPDLOG_DEBUG("updating general status");
			auto query = query::GeneralGetInfo(stdext::span<GlobalInfo>(&state.global, 1));
			auto result = rs.ChannelWriteRead(query.command);
			if(result) {
				auto parserResult = query.parser(*result);
				Update1D(parserResult, query);
			}

			//auto plcQuery = query::GeneralGetPlcStatus(stdext::make_span(state.global.plcs), 0, MAX_PLC-1);
			//auto plcResult = rs.ChannelWriteRead(plcQuery.command);
			//if(plcResult) {
			//	auto parserResult = query.parser(*result);
			//	Update1D(parserResult, query);
			//}
		}

		void UpdateMotorValues() {
			std::lock_guard<std::mutex> lock(stateMutex);
			SPDLOG_DEBUG("updating motor status");
			auto motorQuery = query::MotorGetInfoRange(stdext::make_span(state.motors), 0, state.global.maxMotors - 1);
			auto motorResult = rs.ChannelWriteRead(motorQuery.command);
			if(motorResult) {
				auto parserResult = motorQuery.parser(*motorResult);
				Update2D(parserResult, motorQuery);
				// now we need to check if some statues changed and if so need to
				// call the status modified callbacks
				// TODO: the callback will be called from another thread.. do we need to lock some shit there?
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
			for_each_in_tuple(query.pointers.memberPointer, [&parseResult, &query](auto objPtr, size_t tupleIndex)
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
					// we extract the parser type from the object and use it to parse the string value
					using parser_type = typename decltype(objPtr)::parser_type;
					// query.pointers.data is a span<T> that points to the first element that we want to update
					// objPtr contains the member pointer offset as .ptr and the parser type that should be used
					(query.pointers.data.data() + offset)->*(objPtr.ptr) = parser_type::convert(value);
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
				for_each_in_tuple(query.pointers.memberPointer, [&](auto objPtr, size_t tupleIndex) {
					size_t valueOffset = (objectIndex * packSize) + tupleIndex;
					size_t objectOffset = objectIndex + query.rangeStart;
					auto& value = parseResult[valueOffset];
					//(query.pointers.data.data() + objectOffset)->*target = value;
					// we extract the parser type from the object and use it to parse the string value
					using parser_type = typename decltype(objPtr)::parser_type;
					// query.pointers.data is a span<T> that points to the first element that we want to update
					// objPtr contains the member pointer offset as .ptr and the parser type that should be used
					(query.pointers.data.data() + objectOffset)->*(objPtr.ptr) = parser_type::convert(value);
				});
			}
		}

		void RunRemoteUpdateTimer() {
			while(shouldUpdate) {
				if(rs.IsConnected()) {
					// we need the max motors count to know how many we need to update
					if(state.global.maxMotors == 0) {
						UpdateGeneralInfo();
						// still no active motors? sleep and continue
						if(state.global.maxMotors == 0) {
							std::this_thread::sleep_for(std::chrono::seconds{1});
							continue;
						}
					}
					sl.lock();
					updateIntervals.Update();
					RemoveElapsedUpdateTimers();
					sl.unlock();
				} else {
					SPDLOG_DEBUG("state holder waiting for connection...");
					std::this_thread::sleep_for(std::chrono::seconds{1});
				}
			} // end
			running = false;
		}

		void UpdateCacheIfElapsed(DataRequestType type) {
			DataRequestInfo& info = lastRequestTimes[type];
			auto now = clock::now();
			//SPDLOG_DEBUG("checking if type {} needs an update time left: {}", (int)type, std::chrono::duration_cast<std::chrono::milliseconds>(now - (info.lastUpdate + info.updateInterval)).count());
			if(now >= info.lastUpdate + info.updateInterval) {
				switch (type) {
					case DataRequestType::Motor:
						UpdateMotorValues();
						break;
					case DataRequestType::Global:
						UpdateGeneralInfo();
						break;
					case DataRequestType::Coord:
						break;
					case DataRequestType::IO:
						break;
				}
				// we dont want to use the previus now as the update may took
				// some time and we want the cache to be set current NOW and not at the time
				// where we checked IF it should be updated
				info.lastUpdate = clock::now();
			} else {
				SPDLOG_DEBUG("update skipped through caching");
			}
		}

		// will be called from the "GetMotor|Coord|etc.." functions
		void CreateUpdateTimer(DataRequestType type) {
			sl.lock();
			DataRequestInfo& info = lastRequestTimes[type];
			if(info.timerHandle == INVALID_HANDLE) {
				CallUpdateFunctionByRequestType(type);
				info.timerHandle = updateIntervals.AddTimer(UpdateTime{info.updateInterval, [this, type](){
					CallUpdateFunctionByRequestType(type);
				}});
				info.lastRequest = clock::now();
				SPDLOG_DEBUG("starting update timer for {}", static_cast<int>(type));
			} else {
				info.lastRequest = clock::now();
			}
			sl.unlock();
		}

		// runns only on the update thread
		void RemoveElapsedUpdateTimers() {
			for(auto& p : lastRequestTimes) {
				DataRequestType type = p.first;
				DataRequestInfo& info = p.second;
				if(info.timerHandle == INVALID_HANDLE) {
					continue;
				}
				if(clock::now() >= info.lastRequest + std::chrono::seconds{10}) {
					updateIntervals.RemoveTimer(info.timerHandle);
					info.timerHandle = INVALID_HANDLE;
					SPDLOG_DEBUG("stopping update timer for {}", static_cast<int>(type));
				}
			}
		}

		void CallUpdateFunctionByRequestType(DataRequestType type) {
			try {
				switch (type) {
					case DataRequestType::Motor:
						UpdateMotorValues();
						break;
					case DataRequestType::Global:
						UpdateGeneralInfo();
						break;
					case DataRequestType::Coord:
						break;
					case DataRequestType::IO:
						break;
				}
			} catch(const RuntimeError& e) {
				SPDLOG_ERROR("exception while updating states:\n{}", StringifyException(std::current_exception(), 4, '>'));
			} catch(std::exception& e) {
				SPDLOG_ERROR("exception while updating states:\n{}", StringifyException(std::current_exception(), 4, '>'));
			}
		}

		CoreNotifyInterface& core;
		RemoteShell& rs;
		bool shouldUpdate;
		bool running;
		bool updateShouldBlock;
		bool isUpdateBlocking;
		std::thread updateThread;
		struct PmacData {
			std::vector<MotorInfo> motors;
			std::vector<IOInfo> ios;
			std::vector<CoordInfo> coords;
			GlobalInfo global;
		} state;
		std::unordered_map<DataRequestType, DataRequestInfo> lastRequestTimes;
		IntervalTimer updateIntervals;
		std::mutex stateMutex;
		FairDualMutex timerMutex;
		TicketSpinLock sl;
	};

}

#endif //POWERPMAC_INTERNALSTATE_H
