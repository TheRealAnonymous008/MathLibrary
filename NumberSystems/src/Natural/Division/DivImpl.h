#pragma once

#include "../NaturalBase.h"

#include "DivModResult.h"
#include "KnuthDivision.h"

namespace MathLib {
	namespace NumberSystems {
		namespace implementation {

			template<typename LHS, typename RHS>
			DivModResult Div(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
				return KnuthDivision(lhs, rhs);
			}
		}
	}
}
