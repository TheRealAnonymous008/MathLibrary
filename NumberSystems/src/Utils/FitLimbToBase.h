#pragma once

#include "../../headers/Fwd.h"

namespace MathLib {
	namespace NumberSystems {
		namespace detail{
			struct FitLimb {
				limb_type value;
				limb_type carry;
			};

			inline FitLimb FitLimbToBase(const limb_type& limb) {
				FitLimb result;
				result.carry = limb / LIMB_BASE;
				result.value = limb % LIMB_BASE;

				return result;
			}
		}
	}
}