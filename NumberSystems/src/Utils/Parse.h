#pragma once 

#include "../../../NumberSystems/headers/Fwd.h"

#include "IsNumericString.h"

#include <algorithm>
#include <string>
#include <vector>

namespace MathLib {
	namespace NumberSystems {
		namespace detail {

			inline string_type ToStringWithPad(limb_type data) {
				data += LIMB_BASE;
				return std::to_string(data).substr(1);
			}

			inline string_type ToStringNoPad(limb_type data) {
				return std::to_string(data);
			}

			inline limb_type StringToDigit(const string_type& str) {
				return strtoull(str.c_str(), NULL, 10);
			}

			inline vector_type Parse(string_type str) {
				str.erase(std::remove(str.begin(), str.end(), ','), str.end());

				if (!IsNumericString(str)) {
					throw InvalidNumericString();
				}

				size_type N = str.size();
				vector_type result;
				string_type buffer = "";

				index_type i = N - 1;

				// Warning! This implementation is dependent on the radix. It assumes base = 10.
				for (i = N - 1; i >= LIMB_BASE_POWER; i -= LIMB_BASE_POWER) {
					buffer = str.substr(i - LIMB_BASE_POWER + 1, LIMB_BASE_POWER);
					result.push_back(StringToDigit(buffer));
				}

				result.push_back(StringToDigit(str.substr(0, i + 1)));

				return result;
			}
		}
	}
}