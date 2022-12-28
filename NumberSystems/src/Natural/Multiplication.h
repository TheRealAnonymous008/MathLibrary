#pragma once

#include "../../Exceptions.h"

#include "Multiplication/Classical.h"
#include "Multiplication/Karatsuba.h"
#include "Natural.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class Multiplication<Natural, LHS, RHS> : public NaturalBase<Multiplication<Natural, LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				Natural result;

				void Calculate() {
					Natural left = lhs.Evaluate();
					Natural right = rhs.Evaluate();

					result = implementation::KaratsubaMultiplication(left, right);
					result.RemoveLeadingZeroes();
				}

			public:
				Multiplication<Natural, LHS, RHS>(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					Calculate();
				}

				auto Evaluate() const {
					return result;
				}

			};
		}


		template<typename LHS, typename RHS>
		detail::Multiplication<Natural, LHS, RHS> operator*(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			return detail::Multiplication<Natural, LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}
	}
}