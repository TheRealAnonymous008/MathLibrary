#pragma once

#include "Integer.h"
#include "Complement.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class Or<Integer,LHS, RHS> : public IntegerBase<Or<Integer,LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				Integer result;

				void Calculate() {
					Integer left = Complement(lhs.Evaluate());
					Integer right = Complement(rhs.Evaluate());

					IntegerSign sign = (left.Sign() == NEGATIVE || right.Sign() == NEGATIVE) ? NEGATIVE : POSITIVE;

					Natural left_m = left.Magnitude();
					Natural right_m = right.Magnitude();

					Natural nat = left_m | right_m;

					result = Decomplement(Integer(sign, nat));

				}


			public:
				Or<Integer,LHS, RHS>(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					Calculate();
				}

				auto Evaluate() const {
					return result;
				}

			};
		}

		template<typename LHS, typename RHS>
		detail::Or<Integer,LHS, RHS> operator|(const IntegerBase<LHS>& lhs, const IntegerBase<RHS>& rhs) {
			return detail::Or<Integer,LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}