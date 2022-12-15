#pragma once

#include "../Natural.h"

#include "../Multiplication.h"
#include "../Subtraction.h"

#include "DivModResult.h"
#include "NormalizeDivisionArgs.h"

namespace MathLib {
	namespace NumberSystems {
		namespace implementation {

			inline NormalizedDivModResult KnuthDivision(const Natural& lhs, const Natural& rhs) {
				DivisionNormalizationResult normalized = NormalizeDivisionArgs(lhs, rhs);

				NormalizedDivModResult result{
					.div{Natural()},
					.mod{lhs}
				};
				
				if (lhs.Size() < rhs.Size()) {
					return result;
				}

				auto A = normalized.numerator;
				auto B = normalized.denominator;

				size_type n = B.Size();
				size_type m = A.Size() - n;

				result.div.AddTrailingZeros(m + 1);
				result.mod = A;
				result.D = normalized.D;

				auto right_msl = B[n - 1];

				for (index_type j = m - 1; j < m; --j) {
					
					auto left_msl = result.mod[n + j] * LIMB_BASE + result.mod[n + j - 1];
					auto q_estimate = left_msl / right_msl;

					result.div[j] = std::min(q_estimate, LIMB_BASE - 1);

					Natural b = Natural(B).AddTrailingZeros(j);
					Natural qb = Natural(result.div[j]) * b;

					if (result.mod < qb) {
						--result.div[j];
						qb -= b;
					}

					result.mod -= qb;

				}

				return result;
			}
		}
	}
}
