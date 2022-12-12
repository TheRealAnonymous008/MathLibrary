#pragma once

#include "../Natural.h"
#include "../NaturalSubtraction.h"
#include "NormalizeDivisionArgs.h"

namespace MathLib {
	namespace NumberSystems {
		namespace implementation {

			template<typename LHS, typename RHS>
			Natural KnuthDivision(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
				DivisionNormalizationResult normalized = NormalizeDivisionArgs(lhs, rhs);
				Natural Q;

				size_type n = rhs.Size();
				size_type m = lhs.Size() - n;
				
				if (m < 0)
					return Q;

				auto A = normalized.numerator;
				auto B = normalized.denominator;

				n = B.Size();
				m = A.Size() - n;

				Q.AddTrailingZeros(m + 1);
				auto right_msl = B[n - 1];

				for (index_type j = m - 1; j < m; --j) {
					
					auto left_msl = A[n + j] * LIMB_BASE + A[n + j - 1];
					auto q_estimate = left_msl / right_msl;

					Q[j] = std::min(q_estimate, LIMB_BASE - 1);

					Natural b = Natural(B).AddTrailingZeros(j);
					Natural qb = Natural(Q[j]) * b;

					if (A < qb) {
						--Q[j];
						qb = qb - b;
					}

					A = A - qb;

				}
				return Q.RemoveLeadingZeroes();
			}
		}
	}
}
