#pragma once

#include "../../Exceptions.h"

#include "Natural.h"

#include "Division/DivImpl.h"
#include "Division/DivModResult.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class Modulo<Natural, LHS, RHS> : public NaturalBase<Modulo<Natural, LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				Natural result;

				void Calculate() {
					
					auto normdiv = implementation::Div(lhs.Evaluate() , rhs.Evaluate());
					result = normdiv.mod / normdiv.D;
				}

			public:
				Modulo<Natural, LHS, RHS>(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					if (rhs == constants::naturals::ZERO) {
						throw DivisionByZero();
					}
					Calculate();
				}

				auto Evaluate() const {
					return result;
				}

			};
		}

		template<typename LHS, typename RHS>
		detail::Modulo<Natural, LHS, RHS>operator%(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			return detail::Modulo<Natural, LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}