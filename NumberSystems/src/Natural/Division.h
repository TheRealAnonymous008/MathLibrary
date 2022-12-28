#pragma once

#include "../../Exceptions.h"

#include "Natural.h"

#include "Division/DivImpl.h"
#include "Division/DivModResult.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class Division<Natural, LHS, RHS> : public NaturalBase<Division<Natural, LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				Natural result;

				void Calculate() {
					Natural left = lhs.Evaluate();
					Natural right = rhs.Evaluate();

					result = implementation::Div(left, right).div;
					result.RemoveLeadingZeroes();
				}

			public:
				Division<Natural, LHS, RHS>(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					if (rhs == constants::naturals::ZERO) {
						throw DivisionByZero();
					}
					if (lhs != constants::naturals::ZERO) {
						Calculate();
					}
				}

				auto Evaluate() const {
					return result;
				}

			};
		}

		template<typename LHS, typename RHS>
		detail::Division<Natural, LHS, RHS>operator/(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			return detail::Division<Natural, LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}