#pragma once 

#include "../../../NumberSystems/headers/Fwd.h"
#include <string>

namespace MathLib {
	namespace NumberSystems {
		namespace detail {
			inline bool IsNumericString(const string_type str) {
				
				OPENMP_PARALLELIZE
				for (auto x : str) {
					if (!std::isdigit(x)) {
						return false;
					}
				}

				return true;
			}
		}
	}
}