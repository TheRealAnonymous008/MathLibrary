#pragma once

#include "../NaturalBase.h"

#include "DivModResult.h"
#include "KnuthDivision.h"

namespace MathLib {
	namespace NumberSystems {
		namespace implementation {

			inline NormalizedDivModResult Div(const Natural& lhs, const Natural& rhs) {
				return KnuthDivision(lhs, rhs);
			}
		}
	}
}
