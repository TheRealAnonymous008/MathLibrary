#pragma once

#include "../Natural.h"
#include "../../Utils/FitLimbToBase.h"

namespace MathLib {
	namespace NumberSystems {
		namespace implementation {

			template<typename LHS, typename RHS>
			Natural ClassicalMultiplication(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
				Natural result;
				
				size_type lsize = lhs.Size();
				size_type rsize = rhs.Size();

				for (index_type r = 0; r < rsize; ++r) {
					Natural limb_number;

					limb_type multiplier_limb = rhs[r];
					limb_type carry = 0;

					for (index_type l = 0; l < lsize; ++l) {
						auto addition = detail::FitLimbToBase(lhs[l] * multiplier_limb + carry);
						carry = addition.carry;
						limb_number.AddMostLimb(addition.value);
					}

					if (carry > 0) {
						limb_number.AddMostLimb(carry);
					}

					result += limb_number.AddTrailingZeros(r);
				}

				return result;
			}
		}
	}
}
