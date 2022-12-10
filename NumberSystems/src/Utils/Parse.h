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

			inline bool IsEven(const string_type& str) {
				return str[str.length() - 1] % 2 == 0;
			}

			inline string_type DivideByTwo(const string_type& str) {
				string_type result = "";


				short next_additive = 0;
				for (auto c : str) {
					short additive = next_additive;

					short cd = c - '0';
					if (cd % 2 == 0) {
						next_additive = 0;
					}
					else {
						next_additive = 5;
					}

					short nd = cd / 2 + additive;
					char rd = nd + '0';


					if (result.length() == 0 && rd == '0')
						continue;

					result += rd;
				}

				return result;
			}

			inline vector_type Parse(string_type str) {
				str.erase(std::remove(str.begin(), str.end(), ','), str.end());

				if (!IsNumericString(str)) {
					throw InvalidNumericString();
				}

				vector_type result;
				string_type curr_str = str;
				string_type buffer = "";

				while (curr_str.size() != 0) {
					auto bit = !IsEven(curr_str);
					curr_str = DivideByTwo(curr_str);

					buffer = std::to_string(bit) + buffer;
					if (buffer.length() >= LIMB_BASE_POWER) {
						result.push_back(std::stoi(buffer, 0, 2));
						buffer = "";
					}
				}

				result.push_back(std::stoi(buffer, 0, 2));
				return result;
			}
		}
	}
}