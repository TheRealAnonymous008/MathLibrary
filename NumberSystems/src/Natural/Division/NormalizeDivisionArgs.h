#pragma once

#include "../Natural.h"

#include "../Multiplication.h"

namespace MathLib {
	namespace NumberSystems {
		namespace implementation {

			struct DivisionNormalizationResult {
				Natural numerator;
				Natural denominator;
				Natural D;
			};

			inline DivisionNormalizationResult NormalizeDivisionArgs(const Natural& lhs, const Natural& rhs) {

				auto right_msl = rhs[rhs.Size() - 1];
				DivisionNormalizationResult result; 

				result.D = Natural((LIMB_BASE) / (right_msl + 1));

				result.numerator = lhs * result.D;
				result.denominator = rhs * result.D;

				return result;
			}
		}
	}
}
