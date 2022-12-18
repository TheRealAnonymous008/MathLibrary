#pragma once

#include "Integer.h"
#include "Ordering.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class IntegerAddition : public IntegerBase<IntegerAddition<LHS, RHS>> {
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

					IntegerSign sign = (left_m > right_m) ? left_s : right_s;
					Natural nat;

					if (left_m > right_m) {
						if (left_s == right_s) {
							nat = left_m + right_m;
						} else {
							nat = left_m - right_m;
						}
					}
					else {
						if (left_s == right_s) {
							nat = left_m + right_m;
						}
						else {
							nat = right_m - left_m;
						}
					}

					result = Integer(sign, nat);
				}


			public:
				IntegerAddition(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					Calculate();
				}

				auto Evaluate() const {
					return result;
				}

			};
		}

		template<typename LHS, typename RHS>
		detail::IntegerAddition<LHS, RHS> operator+(const IntegerBase<LHS>& lhs, const IntegerBase<RHS>& rhs) {
			return detail::IntegerAddition(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}