#pragma once 

#include "../../../NumberSystems/headers/Fwd.h"
#include <vector>
#include <string>

namespace MathLib {
	namespace NumberSystems {
		namespace detail {
			inline std::vector<data_type> Parse(const string_type str) {
				size_type N = str.size();
				std::vector<data_type> result;

				for (index_type i = 0; i < N; i += DIGIT_BASE_POWER) {
					result.push_back(stoi(str.substr(i, DIGIT_BASE_POWER)));
				}

				return result;
			}
		}
	}
}