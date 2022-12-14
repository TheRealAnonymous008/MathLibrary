#pragma once

#include "../../Exceptions.h"

#include "Natural.h"

#include "Division/DivImpl.h"
#include "Division/DivModResult.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class NaturalModulo : public NaturalBase<NaturalModulo<LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				Natural result;

				void Calculate() {
					auto normdiv = implementation::Div(lhs, rhs);
					result = normdiv.mod / normdiv.D ;
				}

			public:
				NaturalModulo(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					if (IsZero(rhs)) {
						throw DivisionByZero();
					}
					Calculate();
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
		detail::NaturalModulo<LHS, RHS> operator%(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			return detail::NaturalModulo(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}