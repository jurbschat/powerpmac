//
// Created by urbschaj on 15.02.19.
//

#ifndef POWERPMAC_SIGNALHANDLER_H
#define POWERPMAC_SIGNALHANDLER_H

#include "pmac/defines.h"
#include "libs/sigs.h"

#include <map>
#include <cstdint>

namespace ppmac {

	class SignalHandler {
	public:
		sigs::Signal<void()>& ConnectionEstablished() {
			return connectionEstablished;
		}
		sigs::Signal<void()>& ConnectionLost() {
			return connectionLost;
		}
		sigs::Signal<void(uint64_t newState, uint64_t changes)>& StatusChanged(MotorID id) {
			return motorStatusChanged[id];
		}
		sigs::Signal<void(uint64_t newState, uint64_t changes)>& CtrlChanged(MotorID id) {
			return motorCtrlChanged[id];
		}
		sigs::Signal<void(uint64_t newState, uint64_t changes)>& StatusChanged(CoordID id) {
			return coordStatusChanged[id];
		}
		sigs::Signal<void(uint32_t axis)>& CoordChanged(CoordID id) {
			return coordChanged[id];
		}
		sigs::Signal<void(bool enabled)>& CompTableChanged(CompensationTableID id) {
			return compTableStatusChanged[id];
		}
		void Clear() {
			connectionEstablished.clear();
			connectionLost.clear();
			motorStatusChanged.clear();
			motorCtrlChanged.clear();
			coordStatusChanged.clear();
			coordChanged.clear();
			compTableStatusChanged.clear();
			/*for(auto& s : motorStatusChanged) {
				s.second.clear();
			}
			for(auto& s : motorStatusChanged) {
				s.second.clear();
			}
			for(auto& s : motorStatusChanged) {
				s.second.clear();
			}
			for(auto& s : motorStatusChanged) {
				s.second.clear();
			}*/
		}
	private:
		sigs::Signal<void()> connectionEstablished;
		sigs::Signal<void()> connectionLost;
		std::map<MotorID, sigs::Signal<void(uint64_t newState, uint64_t changes)>> motorStatusChanged;
		std::map<MotorID, sigs::Signal<void(uint64_t newState, uint64_t changes)>> motorCtrlChanged;
		std::map<CoordID, sigs::Signal<void(uint64_t newState, uint64_t changes)>> coordStatusChanged;
		std::map<CoordID, sigs::Signal<void(uint32_t axis)>> coordChanged;
		std::map<CompensationTableID, sigs::Signal<void(bool enabled)>> compTableStatusChanged;
	};

}

#endif //POWERPMAC_SIGNALHANDLER_H
