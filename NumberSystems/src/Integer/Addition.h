#pragma once

#include "Integer.h"
#include "Ordering.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class Addition<Integer, LHS, RHS> : public IntegerBase<Addition<Integer, LHS, RHS>> {
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

					if (left_s == right_s) {
						nat = left_m + right_m;
						sign = left_s;
					}
					else {
						if (left_m > right_m) {
							nat = left_m - right_m;
							sign = left_s;
						}
						else {
							nat = right_m - left_m;
							sign = right_s;
						}
					}

					result = Integer(sign, nat);
				}


			public:
				Addition<Integer, LHS, RHS>(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					Calculate();
				}

				auto Evaluate() const {
					return result;
				}

			};
		}

		template<typename LHS, typename RHS>
		detail::Addition<Integer, LHS, RHS> operator+(const IntegerBase<LHS>& lhs, const IntegerBase<RHS>& rhs) {
			return detail::Addition<Integer, LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}