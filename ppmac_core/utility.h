//
// Created by urbschaj on 16.01.19.
//

#ifndef POWERPMAC_UTILITY_H
#define POWERPMAC_UTILITY_H

#include "pmac/defines.h"
#include <cstdint>
#include <tuple>
#include <array>

namespace ppmac {

	/*template<class Type, class Next>
	bool IsOneOf(const Type& needle, const Next& next)
	{
		return needle == next;
	}

	template<class Type, class Next, class ... Rest>
	bool IsOneOf(const Type& needle, const Next& next, Rest... rest)
	{
		return needle == next || is_one_of(needle, rest...);
	}*/

	template<class VarType, class... Params>
	bool IsOneOf(const VarType& needle, const Params&... params)
	{
		return ((needle == params) || ...);
	}

	namespace detail
	{
		template<int... Is>
		struct seq { };

		template<int N, int... Is>
		struct gen_seq : gen_seq<N - 1, N - 1, Is...> { };

		template<int... Is>
		struct gen_seq<0, Is...> : seq<Is...> { };

		template<typename T, typename F, int... Is>
		void for_each(T&& t, F f, seq<Is...>)
		{
			//auto l = { (f(std::get<Is>(t), Is), 0)... };
			((f(std::get<Is>(t), Is), 0), ...);
		}
	}

	template<typename... Ts, typename F>
	void for_each_in_tuple(std::tuple<Ts...> const& t, F f)
	{
		detail::for_each(t, f, detail::gen_seq<sizeof...(Ts)>());
	}

	template<int... Args>
	struct IsSorted {
		static constexpr bool value = true;
	};

	template<int A, int B, int... Args>
	struct IsSorted<A, B, Args...> {
		static constexpr bool value = A <= B && IsSorted<B, Args...>::value;
	};

	template<int... Args>
	struct IsSortedAndUnique {
		static constexpr bool value = true;
	};

	template<int A, int B, int... Args>
	struct IsSortedAndUnique<A, B, Args...> {
		static constexpr bool value = A < B && IsSorted<B, Args...>::value;
	};

	template<typename... Args>
	bool PackIsSorted(Args... args) {
		return (static_cast<int>(args) < ...);
	}

	template<typename T, typename... Args>
	std::array<T, sizeof...(Args)> PackAsArray(Args... args) {
		std::array<T, sizeof...(Args)> vals = {(static_cast<int>(args), ...)};
		return vals;
	}

}

#endif //POWERPMAC_UTILITY_H
