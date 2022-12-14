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
					size_type l_size = lhs.Size();
					size_type r_size = rhs.Size();

					size_type size = std::min(l_size, r_size);
					index_type i = 0;

					result.AddTrailingZeros(std::max(l_size, r_size));

					OPENMP_PARALLELIZE
					for (i = 0; i < size; ++i) {
						result[i] = lhs[i] ^ rhs[i];
					}

					OPENMP_PARALLELIZE
					for (i; i < l_size; ++i) {
						result[i] = lhs[i];
					}

					OPENMP_PARALLELIZE
					for (i; i < r_size; ++i) {
						result[i] = rhs[i];
					}

					result.RemoveLeadingZeroes();
				}


			public:
				NaturalXor(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
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
		detail::NaturalXor<LHS, RHS> operator^(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			return detail::NaturalXor(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}