//
// Created by urbschaj on 07.03.19.
//

#include "stateupdater.h"
#include "commandbuilder.h"
#include "commandquery.h"
#include "stopwatch.h"
#include "utility.h"
#include "threading.h"
#include "pmac/defines.h"
#include "pmac/datastructures.h"
#include "pmac/enumadapt.h"

#include <boost/regex.hpp>

namespace ppmac {

	StateUpdater::DataRequestInfo StateUpdater::MakeDataRequestInfo(std::chrono::microseconds updateInterval, std::chrono::milliseconds timeout) {
		return DataRequestInfo{
			time_point{},
			//time_point{},
			updateInterval,
			timeout,
			INVALID_HANDLE
		};
	}

	StateUpdater::StateUpdater(CoreNotifyInterface& core, RemoteShell& rs)
		: core(core),
		rs(rs),
		state{},
		motorOrCoordOutOfSync(true)
	{
		state.motors.resize(MAX_MOTORS);
		state.ios.resize(MAX_PORTS);
		state.coords.resize(MAX_COORDS);
		//plcs.resize(MAX_PLC);

		lastRequestTimes[DataRequestType::Global] =         MakeDataRequestInfo(std::chrono::milliseconds{1000}, std::chrono::seconds{10});
		lastRequestTimes[DataRequestType::GlobalSecondary] =MakeDataRequestInfo(std::chrono::milliseconds{3100}, std::chrono::hours{0xFFFFFFFF});
		lastRequestTimes[DataRequestType::Motor] =          MakeDataRequestInfo(std::chrono::milliseconds{50}, std::chrono::seconds{10});
		lastRequestTimes[DataRequestType::MotorSecondary] = MakeDataRequestInfo(std::chrono::milliseconds{2900}, std::chrono::hours{0xFFFFFFFF});
		lastRequestTimes[DataRequestType::Coord] =          MakeDataRequestInfo(std::chrono::milliseconds{50}, std::chrono::seconds{10});
		lastRequestTimes[DataRequestType::IO] =             MakeDataRequestInfo(std::chrono::milliseconds{100}, std::chrono::seconds{10});
	}

	StateUpdater::~StateUpdater() {}

	MotorInfo StateUpdater::GetMotorInfoAndStartTimer(MotorID id) {
		int32_t idx = int32_t(id);
		if(idx >= static_cast<int32_t>(state.motors.size())) {
			THROW_RUNTIME_ERROR("invalid motor id {}, valid: [{}, {}]", id, 0, state.motors.size());
		}
		//UpdateIfElapsed(DataRequestType::Motor);
		CreateUpdateTimer(DataRequestType::Motor);
		return state.motors[idx];
	}

	IOInfo StateUpdater::GetIoInfoAndStartTimer(IoID id) {
		int32_t idx = int32_t(id);
		if(idx >= static_cast<int32_t>(state.ios.size())) {
			THROW_RUNTIME_ERROR("invalid IO id {}, valid: [{}, {}]", id, 0, state.ios.size());
		}
		//UpdateIfElapsed(DataRequestType::IO);
		CreateUpdateTimer(DataRequestType::IO);
		return state.ios[idx];
	}

	CoordInfo StateUpdater::GetCoordInfoAndStartTimer(CoordID id) {
		int32_t idx = int32_t(id);
		if(idx >= static_cast<int32_t>(state.coords.size())) {
			THROW_RUNTIME_ERROR("invalid coord id {}, valid: [{}, {}]", id, 0, state.coords.size());
		}
		CreateUpdateTimer(DataRequestType::Coord);
		return state.coords[idx];
	}

	GlobalInfo StateUpdater::GetGlobalInfoAndStartTimer() {
		CreateUpdateTimer(DataRequestType::Global);
		return state.global;
	}

	std::vector<CoordAxisDefinitionInfo> StateUpdater::GetMotorAxisDefinitions(CoordID id) {
		std::unordered_map<int32_t, std::vector<CoordAxisDefinitionInfo>> out;
		for(int i = 0; i < state.global.maxMotors; i++) {
			auto cmd = cmd::detail::MotorGetCoordAxisDefinition(i);
			auto result = rs.ChannelWriteRead(cmd);
			if(result) {
				try {
					auto cadi = parser::ParseCoordAxisQueryResult(*result);
					out[cadi.coordId].push_back(cadi);
				} catch(const std::exception&) {
					RETHROW_RUNTIME_ERROR("unable to query axis to motor mapping:\nquery: '{}'\nresult: '{}'", cmd, *result);
				}
			}
			else {
				SPDLOG_ERROR("unable to get axis mapping result, channel error: {}", wise_enum::to_string(result.error()));
			}
		}
		return out[static_cast<int32_t>(id)];
	};

	std::experimental::optional<PmacExecutableInfo> StateUpdater::GetPlcInfo(int32_t id) const {
		for(auto& plc : plcs) {
			if(plc.id == id) {
				return plc;
			}
		}
		return std::experimental::optional<PmacExecutableInfo>{};
	}

	int32_t StateUpdater::GetPlcCount() const {
		return plcs.size();
	}

	void StateUpdater::SetPLC(const std::string& str) {
		std::vector<std::string> programs;
		boost::algorithm::split(programs, str, boost::is_any_of("\r\n"), boost::token_compress_on);
		if(programs.empty()) {
			SPDLOG_DEBUG("no plc's or motion programs found");
			return;
		}
		else {
			programs.pop_back();
		}
		for(auto& s : programs) {
			boost::regex rgx(R"(^\W*(\w+)\W+(\w+)\W+(\w+)\W+(\w+)\W*$)");
			boost::smatch what;
			if(boost::regex_search(s, what, rgx)) {
				try {
					//auto internalName = what[1];
					auto enumVal = wise_enum::from_string<PmacExecutableType>(what[2].str().c_str());
					PmacExecutableType type = enumVal.value();
					std::string name = what[3];
					int32_t id = parser::IntParser::convert(what[4]);
					plcs.push_back(PmacExecutableInfo{ name, id, type });
				} catch(const std::exception&) {
					SPDLOG_WARN("unable to parse plc '{}'", s);
				}
			} else {
				SPDLOG_WARN("invalid plc entry: '{}'", s);
			}
		}
	}

	/*MotorUnit GetMotorUnit(MotorID id) {
		auto cmd = cmd::detail::MotorGetUnit(static_cast<int32_t>(id));
		auto result = rs.ChannelWriteRead(cmd);
		if(result) {
			try {
				auto unitAsInt = parser::IntParser::convert(*result);
				return static_cast<MotorUnit>(unitAsInt);
			} catch (const std::exception &) {
				RETHROW_RUNTIME_ERROR("unable to query motor unit:\nquery: '{}'\nresult: '{}'", cmd, *result);
			}
		}
		else {
			SPDLOG_ERROR("unable to get motor unit result, channel error: {}", wise_enum::to_string(result.error()));
		}
		return MotorUnit::None;
	};*/

	void StateUpdater::UpdateGeneralInfo() {
		auto query = query::GeneralGetInfo(stdext::span<GlobalInfo>(&state.global, 1));
		auto result = rs.ChannelWriteRead(query.command);
		if(result) {
			try {
				if(parser::detail::CheckForError(*result)) {
					THROW_RUNTIME_ERROR("response contained error '{}'", *result);
				}
				auto parserResult = query.splitter(*result);
				Update1D(parserResult, query);
				motorOrCoordOutOfSync = false;
			} catch(const std::exception&) {
				RETHROW_RUNTIME_ERROR("unable to update general info:\nquery: '{}'\nresult: '{}'", query.command, *result);
			}
		} else {
			SPDLOG_ERROR("unable to get general result, channel error: {}", wise_enum::to_string(result.error()));
		}
	}

	void StateUpdater::UpdateSecondaryGeneralInfo() {
		auto query = query::GeneralGetInfo(stdext::span<GlobalInfo>(&state.global, 1));
		auto result = rs.ChannelWriteRead(query.command);
		if(result) {
			try {
				if(parser::detail::CheckForError(*result)) {
					THROW_RUNTIME_ERROR("response contained error '{}'", *result);
				}
				auto parserResult = query.splitter(*result);
				Update1D(parserResult, query);
				int32_t seenAsActive = state.global.prevActiveCompensationTables;
				int32_t actuallyActive = state.global.activeCompensationTables;
				bool enableTable = (actuallyActive - seenAsActive) > 0;
				int32_t startUpdate = std::min(seenAsActive, actuallyActive);
				int32_t stopUpdate = std::max(seenAsActive, actuallyActive);
				for(int32_t i = startUpdate; i < stopUpdate; i++) {
					core.OnCompensationTablesChanged(CompensationTableID(i), enableTable);
				}
				state.global.prevActiveCompensationTables = state.global.activeCompensationTables;
			} catch(const std::exception&) {
				RETHROW_RUNTIME_ERROR("unable to update secondary motor values:\nquery: '{}'\nresult: '{}'", query.command, *result);
			}
		} else {
			SPDLOG_ERROR("unable to get secondary motor values, channel error: {}", wise_enum::to_string(result.error()));
		}
	}

	void StateUpdater::UpdateMotorValues() {
		if(state.global.maxMotors == 0) {
			return;
		}
		auto query = query::MotorGetInfoRange(stdext::make_span(state.motors), 0, state.global.maxMotors - 1);
		auto result = rs.ChannelWriteRead(query.command);
		if(result) {
			try {
				auto error = parser::detail::GetError(*result);
				// we have an invalid count of motor/coords we need to request
				// the right values again
				if (error && error->first == parser::EC::OUT_OF_RANGE_NUMBER) {
					motorOrCoordOutOfSync = true;
					SPDLOG_WARN("motor count out of sync, request refresh");
					return;
				}
					// otherwise we just throw the error and handle it further up
				else if (error) {
					THROW_RUNTIME_ERROR("response contained error '{}'", *result);
				}
				auto parserResult = query.splitter(*result);
				Update2D(parserResult, query);
				// now we need to check if some statues changed and if so need to
				// call the status modified callbacks
				// TODO: the callback will be called from another thread.. do we need to lock some shit there?
				for (size_t i = 0; i < state.motors.size(); i++) {
					auto &motor = state.motors[i];
					if (motor.status.registerValue != motor.prevStatus.registerValue) {
						uint64_t changes = motor.prevStatus.registerValue ^motor.status.registerValue;
						core.OnMotorStateChanged(MotorID(i), motor.status.registerValue, changes);
						//PrintStateChanges(i, m.prevStatus.registerValue, m.status.registerValue);
						motor.prevStatus = motor.status;
					}
				}
			} catch (const std::exception&) {
				RETHROW_RUNTIME_ERROR("unable to update motor info:\nquery: '{}'\nresult: '{}'", query.command, *result);
			}
		}
		else {
			SPDLOG_ERROR("unable to get motor result, channel error: {}", wise_enum::to_string(result.error()));
		}
	}

	void StateUpdater::UpdateMotorSecondaryValues() {
		auto query = query::MotorGetSecondaryValues(stdext::make_span(state.motors), 0, state.global.maxMotors - 1);
		auto result = rs.ChannelWriteRead(query.command);
		if(result) {
			try {
				if(parser::detail::CheckForError(*result)) {
					THROW_RUNTIME_ERROR("response contained error '{}'", *result);
				}
				auto parserResult = query.splitter(*result);
				Update1D(parserResult, query);
				for(size_t i = 0; i < state.motors.size(); i++) {
					auto& motor = state.motors[i];
					if(motor.servoCtrl != motor.prevServoCtrl) {
						core.OnMotorCtrlChanged(MotorID(i), bits::set(0ull, AuxMotorStatusBits::ServoCtrl, motor.servoCtrl), bits::set(0ull, AuxMotorStatusBits::ServoCtrl));
						motor.prevServoCtrl = motor.servoCtrl;
					}
				}
			} catch(const std::exception&) {
				RETHROW_RUNTIME_ERROR("unable to update secondary motor values:\nquery: '{}'\nresult: '{}'", query.command, *result);
			}
		} else {
			SPDLOG_ERROR("unable to get secondary motor values, channel error: {}", wise_enum::to_string(result.error()));
		}
	}

	void StateUpdater::UpdateCoordValues() {
		if(state.global.maxCoords == 0) {
			return;
		}
		auto query = query::CoordGetInfoRange(stdext::make_span(state.coords), 0, state.global.maxCoords - 1);
		auto result = rs.ChannelWriteRead(query.command);
		if(result) {
			try {
				auto error = parser::detail::GetError(*result);
				// we have an invalid count of motor/coords we need to request
				// the right values again
				if (error && error->first == parser::EC::OUT_OF_RANGE_NUMBER) {
					motorOrCoordOutOfSync = true;
					SPDLOG_WARN("coord count out of sync, request refresh");
					return;
				}
					// otherwise we just throw the error and handle it further up
				else if (error) {
					THROW_RUNTIME_ERROR("response contained error '{}'", *result);
				}
				auto parserResult = query.splitter(*result);
				UpdateCoord(parserResult, query);
				// notofy for state changes
				for (size_t i = 0; i < state.coords.size(); i++) {
					auto &coord = state.coords[i];
					if (coord.status.registerValue != coord.prevStatus.registerValue) {
						uint64_t changes = coord.status.registerValue ^coord.prevStatus.registerValue;
						core.OnCoordStateChanged(CoordID(i), coord.status.registerValue, changes);
						coord.prevStatus = coord.status;
					}
				}
				// notify for axis changes
				for (size_t i = 0; i < state.coords.size(); i++) {
					auto &coord = state.coords[i];
					if (coord.availableAxis != coord.prevAvailableAxis) {
						core.OnCoordAxisChanged(CoordID(i), coord.availableAxis);
						coord.prevAvailableAxis = coord.availableAxis;
					}
				}
			} catch (const std::exception&) {
				RETHROW_RUNTIME_ERROR("unable to update coord info:\nquery: '{}'\nresult: '{}'", query.command, *result);
			}
		}
		else {
			SPDLOG_ERROR("unable to get coord result, channel error: {}", wise_enum::to_string(result.error()));
		}
	}

	void StateUpdater::PrintStateChanges(size_t motor, uint64_t was, uint64_t is) {
		//fmt::print("MOTOR: {}\n", motor);
		//fmt::print("old {:B}\n", was);
		//fmt::print("new {:B}\n", is);
		for(int i = 0; i < 64; i++) {
			bool a = bits::isSet(was, i);
			bool b = bits::isSet(is, i);
			if(a != b) {
				auto name = wise_enum::to_string(static_cast<MotorStatusBits::TYPE>(i));
				//fmt::print("{} changed {}->{}\n", name, a, b);
			}
		}
	}

	/*void StateUpdater::RunRemoteUpdateTimer() {
		while(shouldUpdate) {
			if(rs.IsConnected()) {
				if(!updateOnce) {
					SetupInitialState();
					SPDLOG_DEBUG("stateupdater initialized");
					core.OnStateupdaterInitialized();
				}
				// we need the max motors count to know how many we need to update
				if(state.global.maxMotors == 0 || motorOrCoordOutOfSync) {
					UpdateGeneralInfo();
					// still no active motors? sleep and continue
					if(state.global.maxMotors == 0) {
						std::this_thread::sleep_for(std::chrono::seconds{1});
						continue;
					}
				}
				std::lock_guard<TicketSpinLock> lock(sl);
				try {
					updateIntervals.Update();
				} catch(std::exception& e) {
					SPDLOG_ERROR("exception in update state timer:\n{}", StringifyException(std::current_exception(), 4, '>'));
				}
				RemoveElapsedUpdateTimers();
			} else {
				//SPDLOG_DEBUG("state holder waiting for connection...");
				std::this_thread::sleep_for(std::chrono::seconds{1});
			}
		} // end
		running = false;
	}*/

	bool StateUpdater::ManualUpdate() {
		// we need the max motors count to know how many we need to update
		if(state.global.maxMotors == 0 || motorOrCoordOutOfSync) {
			UpdateGeneralInfo();
			// still no active motors? sleep and continue
			if(state.global.maxMotors == 0) {
				return false;
			}
		}
		try {
			updateIntervals.Update();
		} catch(std::exception& e) {
			SPDLOG_ERROR("exception in state update:\n{}", StringifyException(std::current_exception(), 4, '>'));
		}
		RemoveElapsedUpdateTimers();
		return true;
	}

	// will be called from the "GetMotor|Coord|etc.." functions
	void StateUpdater::CreateUpdateTimer(DataRequestType type) {
		if(!rs.IsConnected()) {
			return;
		}
		DataRequestInfo& info = lastRequestTimes[type];
		if(info.timerHandle == INVALID_HANDLE) {
			CallUpdateFunctionByRequestType(type);
			info.timerHandle = updateIntervals.AddTimer(UpdateTime{info.updateInterval, [this, type](){
				CallUpdateFunctionByRequestType(type);
			}});
			info.lastRequest = clock::now();
			SPDLOG_DEBUG("starting update timer for {}", wise_enum::to_string(type));
		} else {
			info.lastRequest = clock::now();
		}
	}

	// runns only on the update thread
	void StateUpdater::RemoveElapsedUpdateTimers() {
		for(auto& p : lastRequestTimes) {
			DataRequestType type = p.first;
			DataRequestInfo& info = p.second;
			if(info.timerHandle == INVALID_HANDLE) {
				continue;
			}
			if(clock::now() >= info.lastRequest + info.timeout) {
				updateIntervals.RemoveTimer(info.timerHandle);
				info.timerHandle = INVALID_HANDLE;
				SPDLOG_DEBUG("stopping update timer for {}", wise_enum::to_string(type));
			}
		}
	}

	void StateUpdater::SetupInitialState() {
		UpdateGeneralInfo();
		CreateUpdateTimer(DataRequestType::MotorSecondary);
		CreateUpdateTimer(DataRequestType::GlobalSecondary);
	}

	void StateUpdater::CallUpdateFunctionByRequestType(DataRequestType type) {
		switch (type) {
			case DataRequestType::Motor:
				UpdateMotorValues();
				break;
			case DataRequestType::MotorSecondary:
				UpdateMotorSecondaryValues();
				break;
			case DataRequestType::GlobalSecondary:
				UpdateSecondaryGeneralInfo();
				break;
			case DataRequestType::Global:
				UpdateGeneralInfo();
				break;
			case DataRequestType::Coord:
				UpdateCoordValues();
				break;
			case DataRequestType::IO:
				break;
		}
	}

}

