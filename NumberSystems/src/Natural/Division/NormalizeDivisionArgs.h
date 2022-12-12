#pragma once

#include "../Natural.h"

namespace MathLib {
	namespace NumberSystems {
		namespace implementation {

			struct DivisionNormalizationResult {
				Natural numerator;
				Natural denominator;
				size_type D;
			};

			template<typename LHS, typename RHS>
			DivisionNormalizationResult NormalizeDivisionArgs(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {

				auto right_msl = rhs[rhs.Size() - 1];
				if (right_msl < LIMB_BASE / 2) {
					DivisionNormalizationResult result; 

					auto D = (LIMB_BASE - 1) / right_msl;
					result.D = D;

					auto left_limbs = lhs.Digits();
					auto right_limbs = rhs.Digits();

					OPENMP_PARALLELIZE
					for (auto d : left_limbs) {
						result.numerator.AddMostLimb(d * D);
					}

					OPENMP_PARALLELIZE
					for (auto d : right_limbs) {
						result.denominator.AddMostLimb(d * D);
					}

					return result;
				}

				DivisionNormalizationResult result;
				result.D = 1;
				result.numerator = lhs;
				result.denominator = rhs;

				return result;
			}
		}
	}
}
