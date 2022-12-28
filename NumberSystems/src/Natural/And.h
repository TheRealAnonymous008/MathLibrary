#pragma once

#include "Natural.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class And<Natural, LHS, RHS> : public NaturalBase<And<Natural, LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				Natural result;

				void Calculate() {
					Natural left = lhs.Evaluate();
					Natural right = rhs.Evaluate();

					size_type size = std::min(left.Size(), right.Size());
					result.AddTrailingZeros(size);

					OPENMP_PARALLELIZE
					for (index_type i = 0; i < size; ++i) {
						result[i] = left[i] & right[i];
					}
				}


			public:
				And<Natural, LHS, RHS>(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					Calculate();

				}

				auto Evaluate() const {
					return result;
				}

			};
		}

		template<typename LHS, typename RHS>
		detail::And<Natural, LHS, RHS> operator&(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			return detail::And<Natural, LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}