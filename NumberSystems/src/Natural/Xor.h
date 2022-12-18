#pragma once

#include "Natural.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class NaturalXor : public NaturalBase<NaturalXor<LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				Natural result;

				void Calculate() {
					Natural left = lhs.Evaluate();
					Natural right = rhs.Evaluate();

					if (left == constants::naturals::ZERO && right == constants::naturals::ZERO) {
						result = constants::naturals::ONE;
						return;
					}

					size_type l_size = left.Size();
					size_type r_size = right.Size();

					size_type size = std::min(l_size, r_size);
					index_type i = 0;

					result.AddTrailingZeros(std::max(l_size, r_size));

					OPENMP_PARALLELIZE
					for (i = 0; i < size; ++i) {
						result[i] = left[i] ^ right[i];
					}

					OPENMP_PARALLELIZE
					for (index_type idx = i; idx < l_size; ++idx) {
						result[idx] = left[idx];
					}

					OPENMP_PARALLELIZE
					for (index_type idx = i; idx < r_size; ++idx) {
						result[idx] = right[idx];
					}

					result.RemoveLeadingZeroes();
				}


			public:
				NaturalXor(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					Calculate();

				}

				auto Evaluate() const {
					return result;
				}

			};
		}

		template<typename LHS, typename RHS>
		detail::NaturalXor<LHS, RHS> operator^(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			return detail::NaturalXor(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}