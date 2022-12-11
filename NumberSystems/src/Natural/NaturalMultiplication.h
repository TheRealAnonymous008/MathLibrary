#pragma once

#include "../../Exceptions.h"

#include "Multiplication/Classical.h"
#include "Multiplication/Karatsuba.h"
#include "Natural.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class NaturalMultiplication : public NaturalBase<NaturalMultiplication<LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				Natural result;

				void Calculate() {
					result = implementation::KaratsubaMultiplication(lhs, rhs);
				}

			public:
				NaturalMultiplication(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
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
		detail::NaturalMultiplication<LHS, RHS> operator*(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			return detail::NaturalMultiplication(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}