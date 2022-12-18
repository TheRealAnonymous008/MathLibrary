#pragma once

#include "Integer.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class IntegerMultiplication : public IntegerBase<IntegerMultiplication<LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				Integer result;

				void Calculate() {
					Integer left = lhs.Evaluate();
					Integer right = rhs.Evaluate();

					IntegerSign sign = (left.Sign() == right.Sign()) ? POSITIVE : NEGATIVE;
					Natural nat = left.Magnitude() * right.Magnitude();

					result = Integer(sign, nat);
				}


			public:
				IntegerMultiplication(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					Calculate();
				}

				auto Evaluate() const {
					return result;
				}

			};
		}

		template<typename LHS, typename RHS>
		detail::IntegerMultiplication<LHS, RHS> operator*(const IntegerBase<LHS>& lhs, const IntegerBase<RHS>& rhs) {
			return detail::IntegerMultiplication(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}