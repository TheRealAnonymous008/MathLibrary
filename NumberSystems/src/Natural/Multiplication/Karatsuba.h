#pragma once

#include "../Natural.h"

#include "Classical.h"

namespace MathLib {
	namespace NumberSystems {
		namespace implementation {

			const unsigned KARATSUBA_THRESHOLD = 15;

			template<const unsigned THRESHOLD = KARATSUBA_THRESHOLD>
			Natural KaratsubaMultiplication(const Natural& lhs, const Natural& rhs) {
				size_type size = std::min(lhs.Size(), rhs.Size());
				size_type half_size = size / 2;

				if (size <= THRESHOLD) {
					return ClassicalMultiplication(lhs, rhs);
				}

				auto ld = lhs.Digits();
				auto rd = rhs.Digits();

				Natural left_lo = vector_type(ld.begin(), ld.begin() + half_size);
				Natural left_hi = vector_type(ld.begin() + half_size, ld.end());

				Natural right_lo = vector_type(rd.begin(), rd.begin() + half_size);
				Natural right_hi = vector_type(rd.begin() + half_size, rd.end());

				Natural z0 = KaratsubaMultiplication<THRESHOLD>(left_lo, right_lo);
				Natural z1 = KaratsubaMultiplication<THRESHOLD>(left_lo + left_hi, right_lo + right_hi);
				Natural z2 = KaratsubaMultiplication<THRESHOLD>(left_hi, right_hi);

				Natural middle = z1 - (z2 + z0);

				Natural result = z0 + middle.AddTrailingZeros(half_size) + z2.AddTrailingZeros(half_size * 2);
				return result;
			}

		}
	}
}
