//
// Created by urbschaj on 16.01.19.
//

#ifndef POWERPMAC_UTILITY_H
#define POWERPMAC_UTILITY_H

#include <cstdint>
#include <tuple>
#include <array>
#include <chrono>
#include <type_traits>

namespace ppmac {

	namespace detail
	{
		// foreach in tuple

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

		// runtime tuple index

		template <std::size_t...Is> struct index_sequence {};

		template <std::size_t N, std::size_t...Is>
		struct build : public build<N - 1, N - 1, Is...> {};

		template <std::size_t...Is>
		struct build<0, Is...> {
			using type = index_sequence<Is...>;
		};

		template <std::size_t N>
		using make_index_sequence = typename build<N>::type;

		template <typename T>
		using remove_reference_t = typename std::remove_reference<T>::type;

		template <class Tuple, class F, std::size_t...Is>
		void tuple_switch(const std::size_t i, Tuple&& t, F&& f, index_sequence<Is...>) {
			[](...){}(
					(i == Is && (
							(void)std::forward<F>(f)(std::get<Is>(std::forward<Tuple>(t))), false))...
			);
		}

		// constexpr filename

		constexpr const char* str_end(const char *str) {
			return *str ? str_end(str + 1) : str;
		}

		constexpr bool str_slant(const char *str) {
			return *str == '/' ? true : (*str ? str_slant(str + 1) : false);
		}

		constexpr const char* r_slant(const char* str) {
			return *str == '/' ? (str + 1) : r_slant(str - 1);
		}
	}

	template<class VarType, class... Params>
	bool IsOneOf(const VarType& needle, const Params&... params)
	{
		return ((needle == params) || ...);
	}

	template<typename... Ts, typename F>
	void for_each_in_tuple(std::tuple<Ts...> const& t, F f)
	{
		detail::for_each(t, f, detail::gen_seq<sizeof...(Ts)>());
	}

	template <class Tuple, class F>
	void tuple_switch(const std::size_t i, Tuple&& t, F&& f) {
		static constexpr auto N = std::tuple_size<detail::remove_reference_t<Tuple>>::value;
		detail::tuple_switch(i, std::forward<Tuple>(t), std::forward<F>(f), detail::make_index_sequence<N>{});
	}

	// checks at compiletime if non template type parameters are a sorted integer list
	template<int... Args>
	struct IsSorted {
		static constexpr bool value = true;
	};

	template<int... Args>
	struct IsSortedAndUnique {
		static constexpr bool value = true;
	};

	template<int A, int B, int... Args>
	struct IsSorted<A, B, Args...> {
		static constexpr bool value = A <= B && IsSorted<B, Args...>::value;
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
		std::array<T, sizeof...(Args)> vals = {static_cast<int>(args)...};
		return vals;
	}

	template <class C, typename T>
	T getPointerType(T C::*v);

	// gets a filename from path at compiletime
	constexpr const char* file_name(const char* str) {
		return detail::str_slant(str) ? detail::r_slant(detail::str_end(str)) : str;
	}

	namespace time {
		static constexpr std::chrono::seconds zero = std::chrono::seconds::zero();
	}

}

#endif //POWERPMAC_UTILITY_H
