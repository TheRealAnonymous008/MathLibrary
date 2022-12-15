#pragma once

#include "../Natural.h"

#include "../Multiplication.h"
#include "../Subtraction.h"

#include "DivModResult.h"
#include "KnuthDivision.h"
#include "NormalizeDivisionArgs.h"

namespace MathLib {
	namespace NumberSystems {
		namespace implementation {

			const unsigned RECURSIVE_THRESHOLD = 5;
			
			template<const unsigned THRESHOLD = RECURSIVE_THRESHOLD>
			DivModResult RecursiveDivision(const Natural& lhs, const Natural& rhs) {
				DivModResult result{
					.div{Natural()},
					.mod{lhs},
				};
				Natural A = lhs;
				Natural B = rhs;

				size_type n = B.Size();
				size_type a = A.Size();
				size_type m = a - n;

				if (a < n + THRESHOLD || n < m) {
					return KnuthDivision(lhs, rhs);
				}

				size_type k = m / 2;

				Natural B0 = B.Slice(0, k);
				Natural B1 = B.Slice(k, n);

				auto D1 = RecursiveDivision<THRESHOLD>(A.Slice(2 * k, a), B1);

				Natural b0k = Natural(B0).AddTrailingZeros(k);
				Natural qb = D1.div * b0k;
				Natural A1 = D1.mod.AddTrailingZeros(2 * k) + A.Slice(0, 2 * k);

				Natural bk = B.AddTrailingZeros(k);
				while (A1 < qb) {
					D1.div--;
					A1 += bk;
				}
				A1 -= qb;

				auto D0 = RecursiveDivision<THRESHOLD>(A1.Slice(k, A1.Size()), B1);
				Natural q0b0 = D0.div * B0;
				Natural A2 = D0.mod.AddTrailingZeros(k) + A.Slice(0, k);

				while (A2 < q0b0) {
					D0.div--;
					A2 += B;
				}

				result.div = D1.div.AddTrailingZeros(k) + D0.div;
				result.mod = A2 - q0b0;
;
				return result;
			}
		}
	}
}
