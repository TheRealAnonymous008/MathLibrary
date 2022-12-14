#pragma once

#include "../../Exceptions.h"

#include "Natural.h"

#include "Division/DivImpl.h"
#include "Division/DivModResult.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class NaturalDivision : public NaturalBase<NaturalDivision<LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				Natural result;

				void Calculate() {
					result = implementation::Div(lhs, rhs).div;
					result.RemoveLeadingZeroes();
				}

			public:
				NaturalDivision(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					if (rhs == Natural()) {
						throw DivisionByZero();
					}
					if (lhs != Natural()) {
						Calculate();
					}
				}

				const vector_type Digits() const {
					return result.Digits();
				}

				auto Evaluate() const {
					return result;
				}

			};
		}

		template<typename LHS, typename RHS>
		detail::NaturalDivision<LHS, RHS> operator/(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			return detail::NaturalDivision(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}