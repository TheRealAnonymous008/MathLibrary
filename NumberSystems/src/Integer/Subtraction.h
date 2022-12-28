#pragma once

#include "Integer.h"
#include "Ordering.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class Subtraction<Integer,LHS, RHS> : public IntegerBase<Subtraction<Integer,LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				Integer result;

				void Calculate() {
					Integer left = lhs.Evaluate();
					Integer right = rhs.Evaluate();

					auto left_m = left.Magnitude();
					auto right_m = right.Magnitude();

					auto left_s = left.Sign();
					auto right_s = right.Sign();

					IntegerSign sign;
					Natural nat;

					if (left_m > right_m) {
						sign = left_s;
						if (right_s == left_s) {
							nat = left_m - right_m;
						}
						else {
							nat = left_m + right_m;
						}
					}
					else {
						sign = NegateSign(right_s);
						if (right_s == left_s) {
							nat = right_m - left_m;
						}
						else {
							nat = right_m + left_m;
						}
					}

					result = Integer(sign, nat);
				}


			public:
				Subtraction<Integer,LHS, RHS>(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					Calculate();
				}

				auto Evaluate() const {
					return result;
				}

			};
		}

		template<typename LHS, typename RHS>
		detail::Subtraction<Integer,LHS, RHS> operator-(const IntegerBase<LHS>& lhs, const IntegerBase<RHS>& rhs) {
			return detail::Subtraction<Integer,LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}