#pragma once

#include "Natural.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class NaturalAnd : public NaturalBase<NaturalAnd<LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				Natural result;

				void Calculate() {
					size_type size = std::min(lhs.Size(), rhs.Size());
					result.AddTrailingZeros(size);

					OPENMP_PARALLELIZE
					for (index_type i = 0; i < size; ++i) {
						result[i] = lhs[i] & rhs[i];
					}
				}


			public:
				NaturalAnd(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
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
		detail::NaturalAnd<LHS, RHS> operator&(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			return detail::NaturalAnd(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}