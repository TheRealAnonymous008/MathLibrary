#pragma once 

#include <iostream>
#include "../Core.h"

#include <math.h>

namespace MathLib {
	namespace NumberSystems {

		constexpr unsigned DIGIT_BASE_POWER = 9;
		const unsigned DIGIT_BASE = static_cast<const unsigned>(pow(10, DIGIT_BASE_POWER));

		using string_type = std::string;
		using index_type = int;
		using size_type = unsigned;
		using data_type = unsigned;

		template<typename Derived>
		class NumberBase;

		class Natural;
	}
}