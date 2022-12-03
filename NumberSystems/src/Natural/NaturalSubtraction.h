#pragma once

#include "Natural.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class NaturalSubtraction : public NaturalBase<NaturalSubtraction<LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				vector_type result;

				const vector_type Calculate() const {
					vector_type digits = vector_type();

					return digits;
				}

			public:
				NaturalSubtraction(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					this->result = Calculate();
				}

				const vector_type Digits() const {
					return result;
				}

				auto Evaluate() const {
					return Natural(result);
				}

			};
		}

		template<typename LHS, typename RHS>
		detail::NaturalSubtraction<LHS, RHS> operator-(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			return detail::NaturalSubtraction(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}