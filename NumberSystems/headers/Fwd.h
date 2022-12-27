#pragma once 

#include "Extern.h"

#include <iostream>
#include <math.h>
#include <vector>

namespace MathLib {
	namespace NumberSystems {

		const unsigned LIMB_BASE_POWER = 30;
		const unsigned LIMB_BASE_RADIX = 2;
		const unsigned long long LIMB_BASE = static_cast<const unsigned long long>(pow(LIMB_BASE_RADIX, LIMB_BASE_POWER));
		const unsigned long long MAX_LIMB_VALUE = LIMB_BASE - 1;

		using string_type = std::string;
		using index_type = unsigned long long;
		using size_type = size_t;
		using signed_size_type = long long;
		using signed_index_type = long long;
		using limb_type = unsigned long long;
		using vector_type = std::vector<limb_type>;

		template<typename Derived>
		class NumberBase;

		class Natural;

		template<typename Derived>
		class IntegerBase;

		class Integer;
		
		template<typename F> class Addition{};
		template<typename F> class Subtraction{};
		template<typename F> class Multiplication{};
		template<typename F> class Division{};
		template<typename F> class Modulo{};
		template<typename F> class Negate{};

		template<typename F> class And {};
		template<typename F> class Or {};
		template<typename F> class Not{};
		template<typename F> class Xor{};
		template<typename F> class LeftShift{};
		template<typename F> class RightShift{};

		template<typename F> class Sin{};
		template<typename F> class Cos{};
		template<typename F> class Tan{};
		template<typename F> class Csc{};
		template<typename F> class Sec{};
		template<typename F> class Cot{};

		template<typename F> class Pow{};
		template<typename F> class Sqrt{};
		template<typename F> class Square{};
		template<typename F> class Factorial{};
	}
}