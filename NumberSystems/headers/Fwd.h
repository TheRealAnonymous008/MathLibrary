#pragma once 

#include <iostream>
#include <math.h>

namespace MathLib {
	namespace NumberSystems {

		constexpr unsigned DIGIT_BASE_POWER = 9;
		const unsigned DIGIT_BASE = static_cast<const unsigned>(pow(10, DIGIT_BASE_POWER));

		using string_type = std::string;
		using index_type = int;
		using size_type = unsigned long long;
		using data_type = unsigned long long;


		namespace detail {
			std::vector<data_type> Parse(const string_type str);
		}

		template<typename Derived>
		class NumberBase;

		class Natural;
	}
}