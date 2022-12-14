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

		using string_type = std::string;
		using index_type = unsigned long long;
		using size_type = size_t;
		using limb_type = unsigned long long;
		using vector_type = std::vector<limb_type>;

		template<typename Derived>
		class NumberBase;

		class Natural;
	}
}