#pragma once 

#include "../../../NumberSystems/headers/Fwd.h"

#include "IsNumericString.h"

#include <vector>
#include <string>

namespace MathLib {
	namespace NumberSystems {
		namespace detail {

			inline string_type ToStringWithPad(data_type data) {
				data += DIGIT_BASE;
				return std::to_string(data).substr(1);
			}

			inline string_type ToStringNoPad(data_type data) {
				return std::to_string(data);
			}

			inline data_type StringToDigit(const string_type& str) {
				return strtoull(str.c_str(), NULL, 10);
			}

			inline vector_type Parse(const string_type str) {
				if (!IsNumericString(str)) {
					throw InvalidNumericString();
				}

				size_type N = str.size();
				vector_type result;

				index_type i = N - 1;
				for (i = N - 1; i >= DIGIT_BASE_POWER; i -= DIGIT_BASE_POWER) {
					result.push_back(StringToDigit(str.substr(i - DIGIT_BASE_POWER + 1, DIGIT_BASE_POWER)));
				}

				result.push_back(StringToDigit(str.substr(0, i + 1)));

				return result;
			}
		}
	}
}