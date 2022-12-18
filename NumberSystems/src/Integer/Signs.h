#pragma once

namespace MathLib {
	namespace NumberSystems {

		enum IntegerSign {
			POSITIVE = 0,
			NEGATIVE = 1
		};

		inline IntegerSign NegateSign(IntegerSign sign) {
			return (sign == POSITIVE) ? NEGATIVE : POSITIVE;
		}
	}
}