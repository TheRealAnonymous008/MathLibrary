#pragma once

#include "../Natural.h"

namespace MathLib {
	namespace NumberSystems {
		namespace implementation {

			struct DivisionNormalizationResult {
				Natural numerator;
				Natural denominator;
				Natural D;
			};

			template<typename LHS, typename RHS>
			DivisionNormalizationResult NormalizeDivisionArgs(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {

				auto right_msl = rhs[rhs.Size() - 1];
				DivisionNormalizationResult result; 

				auto D = (LIMB_BASE) / (right_msl + 1);
				result.D = Natural(D);

				result.numerator = lhs * result.D;
				result.denominator = rhs * result.D;

				return result;
			}
		}
	}
}
