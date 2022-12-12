#pragma once

#include "../Natural.h"
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

				if (m < 0) {
					return Q;
				}

				auto A = normalized.numerator;
				auto B = normalized.denominator;

				Q.AddTrailingZeros(m);

				for (index_type j = m - 1; j < m; --j) {
					Q[j] = (A[n + j] * LIMB_BASE, +A[n + j - 1]) / B[n - 1];
					Q[j] = std::min(Q[j], LIMB_BASE - 1);

					Natural qb = Natural(Q[j]);
					qb.AddTrailingZeros(j);


					A = A - qb * B;

					if (j == 0)
						break;
				}

				return Q;
			}
		}
	}
}
