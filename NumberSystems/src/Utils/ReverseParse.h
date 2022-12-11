#pragma once 

#include "../../../NumberSystems/headers/Fwd.h"

#include "IsNumericString.h"
#include "RadixStrings.h"

#include <algorithm>
#include <bitset>
#include <string>
#include <vector>

namespace MathLib {
	namespace NumberSystems {
		namespace detail {

			inline string_type RemoveLeadingZeros(const string_type& str) {
				auto idx = str.find_first_not_of('0');
				if (idx < str.length())
					return str.substr(idx);
				return "";
			}

			inline string_type VecToBinary(const vector_type& vec) {
				string_type result = "";

				for (auto d : vec) {
					auto bits = std::bitset<LIMB_BASE_POWER>(d);
					result = bits.to_string() + result;
				}

				return result;
			}

			inline string_type ReverseParse(const vector_type& str) {

				if (str.size() == 0) {
					return "0";
				}

				string_type binary_string = VecToBinary(str);
				string_type result = "";

				while (binary_string.length() != 0) {
					auto div_result = detail::BinDivideByTen(binary_string);
					binary_string = RemoveLeadingZeros(div_result.first);

					char digit = div_result.second + '0';
					result = (digit) + result;
				}

				return result;
			}
		}
	}
}