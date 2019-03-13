//
// Created by urbschaj on 15.02.19.
//

#ifndef POWERPMAC_SIGNALHANDLER_H
#define POWERPMAC_SIGNALHANDLER_H

#include "pmac/defines.h"
#include "libs/sigs.h"
#include "scopedsignal.h"

#include <map>
#include <cstdint>

namespace ppmac {

	class SignalHandler {
	public:
		template<typename T>
		auto ConnectionEstablished(T t) {
			std::lock_guard<std::mutex> lock(sigMutex);
			auto conn = connectionEstablished.connect(t);
			auto autoSignal = ScopedSignal(conn, [this](sigs::Connection c){
				RemoveConnectionEstablished(c);
			});
			return autoSignal;
		}
		template<typename T>
		auto ConnectionLost(T t) {
			std::lock_guard<std::mutex> lock(sigMutex);
			auto conn = connectionLost.connect(t);
			auto autoSignal = ScopedSignal(conn, [this](sigs::Connection c){
				RemoveConnectionLost(c);
			});
			return autoSignal;
		}
		template<typename T>
		auto StatusChanged(MotorID id, T t) {
			std::lock_guard<std::mutex> lock(sigMutex);
			auto conn = motorStatusChanged[id].connect(t);
			auto autoSignal = ScopedSignal(conn, [id, this](sigs::Connection c){
				RemoveStatusChanged(id, c);
			});
			return autoSignal;
		}
		template<typename T>
		auto CtrlChanged(MotorID id, T t) {
			std::lock_guard<std::mutex> lock(sigMutex);
			auto conn = motorCtrlChanged[id].connect(t);
			auto autoSignal = ScopedSignal(conn, [id, this](sigs::Connection c){
				RemoveCtrlChanged(id, c);
			});
			return autoSignal;
		}
		template<typename T>
		auto StatusChanged(CoordID id, T t) {
			std::lock_guard<std::mutex> lock(sigMutex);
			auto conn = coordStatusChanged[id].connect(t);
			auto autoSignal = ScopedSignal(conn, [id, this](sigs::Connection c){
				RemoveStatusChanged(id, c);
			});
			return autoSignal;
		}
		template<typename T>
		auto CoordChanged(CoordID id, T t) {
			std::lock_guard<std::mutex> lock(sigMutex);
			auto conn = coordChanged[id].connect(t);
			auto autoSignal = ScopedSignal(conn, [id, this](sigs::Connection c){
				RemoveCoordChanged(id,c);
			});
			return autoSignal;
		}
		template<typename T>
		auto CompTableChanged(CompensationTableID id, T t) {
			std::lock_guard<std::mutex> lock(sigMutex);
			auto conn = compTableStatusChanged[id].connect(t);
			auto autoSignal = ScopedSignal(conn, [id, this](sigs::Connection c){
				RemoveCompTableChanged(id,c);
			});
			return autoSignal;
		}

		void RemoveConnectionEstablished(sigs::Connection c) {
			std::lock_guard<std::mutex> lock(sigMutex);
			connectionEstablished.disconnect(c);
		}
		void RemoveConnectionLost(sigs::Connection c) {
			std::lock_guard<std::mutex> lock(sigMutex);
			connectionLost.disconnect(c);
		}
		void RemoveStatusChanged(MotorID motorID, sigs::Connection c) {
			std::lock_guard<std::mutex> lock(sigMutex);
			motorStatusChanged[motorID].disconnect(c);
		}
		void RemoveCtrlChanged(MotorID motorID, sigs::Connection c) {
			std::lock_guard<std::mutex> lock(sigMutex);
			motorCtrlChanged[motorID].disconnect(c);
		}
		void RemoveStatusChanged(CoordID coordID, sigs::Connection c) {
			std::lock_guard<std::mutex> lock(sigMutex);
			coordStatusChanged[coordID].disconnect(c);
		}
		void RemoveCoordChanged(CoordID coordID, sigs::Connection c) {
			std::lock_guard<std::mutex> lock(sigMutex);
			coordChanged[coordID].disconnect(c);
		}
		void RemoveCompTableChanged(CompensationTableID compensationTableID, sigs::Connection c) {
			std::lock_guard<std::mutex> lock(sigMutex);
			compTableStatusChanged[compensationTableID].disconnect(c);
		}
		void Clear() {
			std::lock_guard<std::mutex> lock(sigMutex);
			connectionEstablished.clear();
			connectionLost.clear();
			motorStatusChanged.clear();
			motorCtrlChanged.clear();
			coordStatusChanged.clear();
			coordChanged.clear();
			compTableStatusChanged.clear();
		}

		void RunConnectionEstablished() {
			std::lock_guard<std::mutex> lock(sigMutex);
			connectionEstablished();
		}
		void RunConnectionLost() {
			std::lock_guard<std::mutex> lock(sigMutex);
			connectionLost();
		}
		void RunStatusChanged(MotorID motorID, uint64_t newState, uint64_t changes) {
			std::lock_guard<std::mutex> lock(sigMutex);
			motorStatusChanged[motorID](std::move(newState), std::move(changes));
		}
		void RunCtrlChanged(MotorID motorID, uint64_t newState, uint64_t changes) {
			std::lock_guard<std::mutex> lock(sigMutex);
			motorCtrlChanged[motorID](std::move(newState), std::move(changes));
		}
		void RunStatusChanged(CoordID coordID, uint64_t newState, uint64_t changes) {
			std::lock_guard<std::mutex> lock(sigMutex);
			coordStatusChanged[coordID](std::move(newState), std::move(changes));
		}
		void RunCoordChanged(CoordID coordID, uint32_t availableAxis) {
			std::lock_guard<std::mutex> lock(sigMutex);
			coordChanged[coordID](std::move(availableAxis));
		}
		void RunCompTableChanged(CompensationTableID compensationTableID, bool active) {
			std::lock_guard<std::mutex> lock(sigMutex);
			compTableStatusChanged[compensationTableID](std::move(active));
		}
	private:
		std::mutex sigMutex;
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
