#pragma once

#include "Natural.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class NaturalOr : public NaturalBase<NaturalOr<LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				Natural result;

				void Calculate() {
					Natural left = lhs.Evaluate();
					Natural right = rhs.Evaluate();

					size_type l_size = left.Size();
					size_type r_size = right.Size();

					size_type size = std::min(l_size , r_size);
					index_type i = 0;

					result.AddTrailingZeros(std::max(l_size, r_size));

					OPENMP_PARALLELIZE
					for (i = 0; i < size; ++i) {
						result[i] = left[i] | right[i];
					}

					OPENMP_PARALLELIZE
					for (index_type idx = i; idx < l_size; ++idx) {
						result[idx] = left[idx];
					}

					OPENMP_PARALLELIZE
					for (index_type idx = i; idx < r_size; ++idx) {
						result[idx] = right[idx];
					}
				}


			public:
				NaturalOr(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					Calculate();

				}

				auto Evaluate() const {
					return result;
				}

			};
		}

		template<typename LHS, typename RHS>
		detail::NaturalOr<LHS, RHS> operator|(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			return detail::NaturalOr(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}