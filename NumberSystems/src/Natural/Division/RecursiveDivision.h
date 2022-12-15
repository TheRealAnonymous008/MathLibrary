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

			const unsigned RECURSIVE_THRESHOLD = 2;
			
			template<const unsigned THRESHOLD = RECURSIVE_THRESHOLD>
			DivModResult RecursiveDivision(const Natural& lhs, const Natural& rhs) {
				DivModResult result{
					.div{Natural()},
					.mod{lhs},
				};

				if (lhs.Size() < rhs.Size() + THRESHOLD) {
					return KnuthDivision(lhs, rhs);
				}

				DivisionNormalizationResult normalized = NormalizeDivisionArgs(lhs, rhs);
				Natural A = normalized.numerator;
				Natural B = normalized.denominator;

				size_type n = B.Size();
				size_type a = A.Size();
				size_type m = a - n;
				size_type k = m / 2;

				Natural B0 = B.Slice(0, k);
				Natural B1 = B.Slice(k, n);

				auto D1 = RecursiveDivision<THRESHOLD>(A.Slice(2 * k, a), B1);
				std::cout << "This ran";

				Natural b0k = Natural(B0).AddTrailingZeros(k);
				Natural bk = B.AddTrailingZeros(k);

				Natural qb = D1.div * b0k;
				Natural A1 = D1.mod.AddTrailingZeros(2 * k) + A.Slice(0, 2 * k);

				while (A1 < qb) {
					D1.div-=Natural("1");
					A1 += bk;
				}
				A1 -= qb;

				auto D0 = RecursiveDivision<THRESHOLD>(A1.AddTrailingZeros(k), B1);
				Natural A2 = D0.mod.AddTrailingZeros(k) + A.Slice(0, k);

				Natural q0b0 = D0.div * B0;
				
				while (A2 < q0b0) {
					D0.div -= Natural("1");
					A2 += B;
				}

				result.div = D1.div.AddTrailingZeros(k) + D0.div;
				result.mod = A2 - q0b0;

				return result;
			}
		}
	}
}
