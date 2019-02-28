//
// Created by urbschaj on 26.02.19.
//

#include "datastructures.h"
#include "enumadapt.h"
#include <fmt/format.h>

namespace ppmac {

	namespace detail {
		template<typename T>
		std::string GetEnumNamesForBitMatch(uint64_t state, uint64_t significantBits, uint64_t expectedState)
		{
			// mask all bits we dont want to check
			fmt::memory_buffer buff;
			bool first = true;
			for (int i = 0; i < 64; i++)
			{
				if(bits::isSet(significantBits, i))
				{
					if(bits::isSet(state, i) == bits::isSet(expectedState, i))
					{
						T e = static_cast<T>(i);
						std::string name = wise_enum::to_string(e);
						fmt::format_to(buff, "{}{}", (first ? "" : ", "), name);
						first = false;
					}
				}
			}
			return fmt::to_string(buff);
		}
	}

	namespace bits {

		bool AllBitsSet(uint64_t state, uint64_t check) {
			return (state & check) == check;
		}

		bool AnyBitSet(uint64_t state, uint64_t check) {
			return (state & check) != 0;
		}
	}

	namespace states {

		std::string GetMotorStateNamesForFlagMatch(uint64_t state, uint64_t checkBits, uint64_t expected) {
			return detail::GetEnumNamesForBitMatch<MotorStatusBits::TYPE>(state, checkBits, expected);
		}
		std::string GetCoordStateNamesForFlagMatch(uint64_t state, uint64_t checkBits, uint64_t expected) {
			return detail::GetEnumNamesForBitMatch<CoordStatusBits::TYPE>(state, checkBits, expected);
		}
	}

}