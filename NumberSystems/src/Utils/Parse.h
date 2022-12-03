#pragma once 

#include "../../../NumberSystems/headers/Fwd.h"

#include "IsNumericString.h"

#include <vector>
#include <string>

namespace MathLib {
	namespace NumberSystems {
		namespace detail {
			inline std::vector<data_type> Parse(const string_type str) {
				if (!IsNumericString(str)) {
					throw InvalidNumericString();
				}

				size_type N = str.size();
				std::vector<data_type> result;

				index_type i = N - 1;
				for (i = N - 1; i >= DIGIT_BASE_POWER; i -= DIGIT_BASE_POWER) {
					result.push_back(stoi(str.substr(i - DIGIT_BASE_POWER + 1, DIGIT_BASE_POWER)));
				}

				result.push_back(stoi(str.substr(0, i + 1)));

				return result;
			}
		}
	}
}