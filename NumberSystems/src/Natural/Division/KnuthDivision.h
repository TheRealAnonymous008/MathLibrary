#pragma once

#include "../Natural.h"
#include "../NaturalSubtraction.h"

#include "DivModResult.h"
#include "NormalizeDivisionArgs.h"

namespace MathLib {
	namespace NumberSystems {
		namespace implementation {

			template<typename LHS, typename RHS>
			DivModResult KnuthDivision(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
				DivisionNormalizationResult normalized = NormalizeDivisionArgs(lhs, rhs);

				DivModResult result{
					.div{Natural()},
					.mod{lhs}
				};

				size_type n = rhs.Size();
				size_type m = lhs.Size() - n;
				
				if (m < 0) {
					return result;
				}

				auto A = normalized.numerator;
				auto B = normalized.denominator;

				n = B.Size();
				m = A.Size() - n;

				result.div.AddTrailingZeros(m + 1);
				result.mod = A;

				auto right_msl = B[n - 1];

				for (index_type j = m - 1; j < m; --j) {
					
					auto left_msl = result.mod[n + j] * LIMB_BASE + result.mod[n + j - 1];
					auto q_estimate = left_msl / right_msl;

					result.div[j] = std::min(q_estimate, LIMB_BASE - 1);

					Natural b = Natural(B).AddTrailingZeros(j);
					Natural qb = Natural(result.div[j]) * b;

					if (result.mod < qb) {
						--result.div[j];
						qb = qb - b;
					}

					result.mod -= qb;

				}

				result.div.RemoveLeadingZeroes();

				return result;
			}
		}
	}
}
