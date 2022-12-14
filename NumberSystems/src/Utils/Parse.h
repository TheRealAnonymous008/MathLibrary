#pragma once 

#include "../../../NumberSystems/headers/Fwd.h"

#include "IsNumericString.h"
#include "RadixStrings.h"

#include <algorithm>
#include <string>
#include <vector>

namespace MathLib {
	namespace NumberSystems {
		namespace detail {

			inline vector_type Parse(string_type str) {
				str.erase(std::remove(str.begin(), str.end(), ','), str.end());

				if (!IsNumericString(str)) {
					throw InvalidNumericString();
				}

				if (str.find_first_not_of("0") == std::string::npos) {
					return vector_type();
				}

				vector_type result;
				string_type curr_str = str;
				string_type buffer = "";

				while (curr_str.size() != 0) {
					auto bit = !IsEven(curr_str);
					curr_str = DecDivideByTwo(curr_str);

					buffer = std::to_string(bit) + buffer;
					if (buffer.length() >= LIMB_BASE_POWER) {
						result.push_back(std::stoi(buffer, 0, 2));
						buffer = "";
					}
				}
				if (buffer.length() != 0) {
					result.push_back(std::stoi(buffer, 0, 2));
				}

				return result;
			}
		}
	}
}