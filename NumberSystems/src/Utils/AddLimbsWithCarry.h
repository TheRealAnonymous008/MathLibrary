#pragma once

#include "../../headers/Fwd.h"

namespace MathLib {
	namespace NumberSystems {
		namespace detail{
			struct LimbAddition {
				limb_type value;
				limb_type carry;
			};

			inline LimbAddition AddLimbsWithCarry(const limb_type& lhs, const limb_type& rhs, const limb_type& carry = 0) {
				LimbAddition result;
				result.value = lhs + rhs + carry;
				result.carry = result.value / LIMB_BASE;
				result.value = result.value % LIMB_BASE;

				return result;
			}
		}
	}
}