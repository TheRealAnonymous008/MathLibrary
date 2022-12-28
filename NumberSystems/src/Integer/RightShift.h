#pragma once

#include "Integer.h"
#include "Complement.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class RightShift<Integer,LHS, RHS> : public IntegerBase<RightShift<Integer,LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				Integer result;

				void Calculate() {
					Integer left = lhs.Evaluate();
					Integer right = rhs.Evaluate();

					if (right.Sign() == NEGATIVE) {
						throw UndefinedBitshift();
					}

					IntegerSign sign = left.Sign();
					Natural nat = left.Magnitude() >> right.Magnitude();

					result = Integer(sign, nat);

				}


			public:
				RightShift<Integer,LHS, RHS>(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					Calculate();
				}

				auto Evaluate() const {
					return result;
				}

			};
		}

		template<typename LHS, typename RHS>
		detail::RightShift<Integer,LHS, RHS> operator>>(const IntegerBase<LHS>& lhs, const IntegerBase<RHS>& rhs) {
			return detail::RightShift<Integer,LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}