#pragma once 

#include "../../../NumberSystems/headers/Fwd.h"
#include "../../../NumberSystems/Exceptions.h"

#include "../Natural/Parse.h"

#include "../Utils/IsNumericString.h"
#include "../Utils/RadixStrings.h"

#include "Signs.h"

#include <algorithm>
#include <string>
#include <vector>

namespace MathLib {
	namespace NumberSystems {
		namespace detail {

			struct ParseIntegerResult {
				vector_type body;
				IntegerSign sign;
			};

			inline ParseIntegerResult ParseInteger(string_type str) {
				str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

				ParseIntegerResult result;

				if (str.size() != 0 && str[0] == '-' && str.find_last_of('-') == 0) {
					result.sign = NEGATIVE;
				}
				else {
					result.sign = POSITIVE;
				}

				str.erase(std::remove(str.begin(), str.end(), '-'), str.end());
				result.body = ParseNatural(str);

				return result;
			}
		}
	}
}