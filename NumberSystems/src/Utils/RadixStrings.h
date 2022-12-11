#pragma once 

#include "../../../NumberSystems/headers/Fwd.h"

#include "IsNumericString.h"

#include <algorithm>
#include <string>
#include <vector>

namespace MathLib {
	namespace NumberSystems {
		namespace detail {

			inline bool IsEven(const string_type& str) {
				return str[str.length() - 1] % 2 == 0;
			}

			inline string_type DecDivideByTwo(const string_type& str) {
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

			inline std::pair<string_type, short> BinDivideByTen(const string_type& str) {
				string_type result = "";

				short buffer = 0;

				for (auto c : str) {
					buffer = buffer << 1;
					buffer = buffer + (c - '0');

					if (buffer >= 10) {
						result += '1';
						buffer -= 10;
					}
					else {
						result += '0';
					}
				}

				return std::pair<string_type, short>(result, buffer);
			}
		}
	}
}