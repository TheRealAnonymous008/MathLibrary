#pragma once 

#include "Extern.h"

#include <iostream>
#include <math.h>
#include <vector>

namespace MathLib {
	namespace NumberSystems {

		const unsigned DIGIT_BASE_POWER = 9;
		const unsigned long long DIGIT_BASE = static_cast<const unsigned long long>(pow(10, DIGIT_BASE_POWER));

		using string_type = std::string;
		using index_type = unsigned long long;
		using size_type = unsigned long long;
		using data_type = unsigned long long;
		using vector_type = std::vector<data_type>;

		template<typename Derived>
		class NumberBase;

		class Natural;
	}
}