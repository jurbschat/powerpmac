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
			motors.resize(MAX_MOTORS);
			ports.resize(MAX_PORTS);
			//TODO: get initial stuff e.g. max motors/coords
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
			if(idx >= static_cast<int32_t>(motors.size())) {
				THROW_RUNTIME_ERROR("invalid motor index");
			}
			return motors[idx];
		}

		PortInfo GetPortInfo(PortID::TYPE id) const {
			int32_t idx = convert::from_enum(id);
			if(idx >= static_cast<int32_t>(ports.size())) {
				THROW_RUNTIME_ERROR("invalid port index");
			}
			return ports[idx];
		}

		void UpdateAllState() {
			// general status
			auto generalQuery = query::GeneralGetInfo();
			auto generalResult = rs.ChannelWriteRead(generalQuery.command);
			if(generalResult) {
				auto parseResult = cmd::ParseMultilineResult<float>(*generalResult);
				UpdateQueryTargets(parseResult, generalQuery);
			}

			// motor status
			auto motorQuery = query::MotorGetPositionRange(MotorID::Motor0, MotorID::Motor8);
			auto motorResult = rs.ChannelWriteRead(motorQuery.command);
			if(motorResult) {
				auto parseResult = cmd::ParseMultilineResult<float>(*motorResult);
				UpdateQueryTargets(parseResult, motorQuery);
			}
		}

		template<typename T, typename U>
		void UpdateQueryTargets(const T &parseResult, const U &query) {
			if(std::tuple_size<decltype(query.targets)>::value != parseResult.size()) {
				THROW_RUNTIME_ERROR("result does not match parser");
			}
			// we iterate over each member pointer in the targets tuple and match those
			// to the actual structs that we want to update
			for_each_in_tuple(query.targets, [this, &parseResult, &query](auto target, size_t idx) {
				(void)query.targets;
				(void)target;
				(void)idx;
				(void)this;
				auto& lineResultVector = parseResult[idx];
				for(size_t i = 0; i < lineResultVector.size(); i++) {
					auto value = lineResultVector[i];
					(void)value;
					//motors[i + query.first].*target = value;
				}
			});
		}

		void UpdateMotors() {

		}

		void UpdateStates() {

		}

	private:
		void QueryPPmacState() {
			running = true;
			while(shouldUpdate) {
				if(rs.IsConnected()) {
					UpdateStates();
					std::this_thread::sleep_for(std::chrono::milliseconds{10});
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
		std::vector<MotorInfo> motors;
		std::vector<PortInfo> ports;
		GlobalInfo global;
	};

}

#endif //POWERPMAC_INTERNALSTATE_H
