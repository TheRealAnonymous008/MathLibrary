#pragma once

#include "Integer.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class Division<Integer, LHS, RHS> : public IntegerBase<Division<Integer, LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				Integer result;

				void Calculate() {
					Integer left = lhs.Evaluate();
					Integer right = rhs.Evaluate();

					IntegerSign sign = (left.Sign() == right.Sign()) ? POSITIVE : NEGATIVE;
					Natural nat = left.Magnitude() / right.Magnitude();

					result = Integer(sign, nat);
				}


			public:
				Division<Integer, LHS, RHS>(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					Calculate();
				}

				auto Evaluate() const {
					return result;
				}

			};
		}

		template<typename LHS, typename RHS>
		detail::Division<Integer, LHS, RHS> operator/(const IntegerBase<LHS>& lhs, const IntegerBase<RHS>& rhs) {
			return detail::Division<Integer, LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}