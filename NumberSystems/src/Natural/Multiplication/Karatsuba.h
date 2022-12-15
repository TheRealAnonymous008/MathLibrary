#pragma once

#include "../Natural.h"

#include "Classical.h"

namespace MathLib {
	namespace NumberSystems {
		namespace implementation {

			const unsigned KARATSUBA_THRESHOLD = 15;

			template<const unsigned THRESHOLD = KARATSUBA_THRESHOLD>
			Natural KaratsubaMultiplication(const Natural& lhs, const Natural& rhs) {
				size_type l_size = lhs.Size();
				size_type r_size = rhs.Size();

				size_type size = std::min(l_size, r_size);
				size_type half_size = size / 2;

				if (size <= THRESHOLD) {
					return ClassicalMultiplication(lhs, rhs);
				}

				Natural left_lo = lhs.Slice(0, half_size);
				Natural left_hi = lhs.Slice(half_size, l_size);

				Natural right_lo = rhs.Slice(0, half_size);
				Natural right_hi = rhs.Slice(half_size, r_size);

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
