//
// Created by urbschaj on 07.03.19.
//

#include <atomic>
#include <mutex>

#ifndef POWERPMAC_LOCKING_H
#define POWERPMAC_LOCKING_H

namespace ppmac {

	class SpinLock {
	public:
		void lock();
		void unlock();
	private:
		std::atomic_flag locked = ATOMIC_FLAG_INIT ;
	};

	class TicketSpinLock
	{
	public:
		void lock();
		void unlock();

	private:
		std::atomic_size_t ServingTicketNo = {0};
		std::atomic_size_t NextTicketNo = {0};
	};

	//struct SpinLockGuard

	class FairDualMutex : public std::mutex {
	public:
		void lock();
	private:
		std::mutex _fairness_mutex;
	};

};

#endif //POWERPMAC_LOCKING_H
