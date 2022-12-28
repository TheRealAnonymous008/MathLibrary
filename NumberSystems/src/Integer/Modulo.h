#pragma once

#include "Integer.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class Modulo<Integer, LHS, RHS> : public IntegerBase<Modulo<Integer, LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				Integer result;

				// Note: The convention adopted here is that the following identity must hold for a, b, q, r
				// q := a / b  
				// r := a % b
				// a := qb + r

				void Calculate() {
					Integer left = lhs.Evaluate();
					Integer right = rhs.Evaluate();

					Natural left_m = left.Magnitude();
					Natural right_m = right.Magnitude();

					Natural nat = left_m % right_m;

					result = Integer(left.Sign(), nat);
				}


			public:
				Modulo<Integer, LHS, RHS>(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					Calculate();
				}

				auto Evaluate() const {
					return result;
				}

			};
		}

		template<typename LHS, typename RHS>
		detail::Modulo<Integer, LHS, RHS> operator%(const IntegerBase<LHS>& lhs, const IntegerBase<RHS>& rhs) {
			return detail::Modulo<Integer, LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}