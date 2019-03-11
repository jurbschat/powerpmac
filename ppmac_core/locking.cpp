//
// Created by urbschaj on 07.03.19.
//


#include "locking.h"

namespace ppmac {

	void SpinLock::lock() {
		while (locked.test_and_set(std::memory_order_acquire)) { ; }
	}
	void SpinLock::unlock() {
		locked.clear(std::memory_order_release);
	}

	////////////////////////////

	void TicketSpinLock::lock()
	{
		const auto myTicketNo = NextTicketNo.fetch_add(1, std::memory_order_relaxed);

		while (ServingTicketNo.load(std::memory_order_acquire) != myTicketNo) {
			__asm__ ( "pause;" );
		}
	}

	void TicketSpinLock::unlock()
	{
		// We can get around a more expensive read-modify-write operation
		// (std::atomic_size_t::fetch_add()), because no one can modify
		// ServingTicketNo while we're in the critical section.
		const auto newNo = ServingTicketNo.load(std::memory_order_relaxed)+1;
		ServingTicketNo.store(newNo, std::memory_order_release);
	}

	////////////////////////////

	void FairDualMutex::lock() {
		_fairness_mutex.lock();
		std::mutex::lock();
		_fairness_mutex.unlock();
	}

}
