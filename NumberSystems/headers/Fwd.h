#pragma once 

#include "Extern.h"

#include <iostream>
#include <math.h>

namespace MathLib {
	namespace NumberSystems {

		const static unsigned DIGIT_BASE_POWER = 9;
		const static unsigned DIGIT_BASE = static_cast<const unsigned>(pow(10, DIGIT_BASE_POWER));

		using string_type = std::string;
		using index_type = int;
		using size_type = unsigned long long;
		using data_type = unsigned long long;


		template<typename Derived>
		class NumberBase;

		class Natural;
	}
}