#pragma once

#include "../NaturalBase.h"

#include "DivModResult.h"

#include "NormalizeDivisionArgs.h"
#include "RecursiveDivision.h"
#include "KnuthDivision.h"

namespace MathLib {
	namespace NumberSystems {
		namespace implementation {

			inline NormalizedDivModResult Div(const Natural& lhs, const Natural& rhs) {
				auto normalized = NormalizeDivisionArgs(lhs, rhs);
				DivModResult result = RecursiveDivision(normalized.numerator, normalized.denominator);

				NormalizedDivModResult ans{
					.div{result.div},
					.mod{result.mod},
					.D{normalized.D},
				};

				return ans;
			}
		}
	}
}
