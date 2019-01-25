//
// Created by urbschaj on 24.01.19.
//

enum class bla {
	A,
	B
};

namespace MotorID {
	enum TYPE: int {
		Motor0,
		Motor1,
		Motor2,
		Motor3,
		Motor4,
		Motor5,
		Motor6,
		Motor7,
		Motor8,
	};
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

template<int... Ts>
constexpr bool ValidateSorted() {
	return IsSorted<Ts...>::value;;
}

template<int... Ts>
struct mystruct {
	float a;
};

template<int... Ts>
mystruct<Ts...> test_fct(float a) {
	return mystruct<Ts...>{a};
}

void bla() {

	auto b = test_fct<1, 2>(0.4);
	(void)b;

	//static_assert(ValidateSorted(MotorID::Motor3, MotorID::Motor3),"");
}

