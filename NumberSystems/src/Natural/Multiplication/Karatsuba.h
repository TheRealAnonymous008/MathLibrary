#pragma once

#include "../Natural.h"

#include "Classical.h"

namespace MathLib {
	namespace NumberSystems {
		namespace implementation {

			const int KARATSUBA_THRESHOLD = 1;

			template<typename LHS, typename RHS>
			Natural KaratsubaMultiplication(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
				size_type size = std::min(lhs.Size(), rhs.Size());
				size_type half_size = size / 2;

				if (size <= KARATSUBA_THRESHOLD) {
					return ClassicalMultiplication(lhs, rhs);
				}

				auto ld = lhs.Digits();
				auto rd = rhs.Digits();

				auto left_lo = Natural(vector_type (ld.begin(), ld.begin() + half_size));
				auto left_hi = Natural(vector_type (ld.begin() + half_size, ld.end()));

				auto right_lo = Natural(vector_type(rd.begin(), rd.begin() + half_size));
				auto right_hi = Natural(vector_type(rd.begin() + half_size, rd.end()));

				Natural z0 = KaratsubaMultiplication(left_lo, right_lo);
				Natural z1 = KaratsubaMultiplication(left_lo + left_hi, right_lo + right_hi);
				Natural z2 = KaratsubaMultiplication(left_hi, right_hi);

				Natural middle = z1 - z2 - z0;

				Natural result = z0 + middle.AddTrailingZeros(half_size) + z2.AddTrailingZeros(half_size * 2);
				return result;
			}

		}
	}
}
