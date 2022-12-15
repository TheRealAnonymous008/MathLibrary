#pragma once

#include "../../Exceptions.h"

#include "Natural.h"
#include "Ordering.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class NaturalSubtraction : public NaturalBase<NaturalSubtraction<LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				Natural result;

				void Calculate() {
					if (rhs > lhs) {
						throw InvalidSubtractionOperation();
					}

					result = lhs.Evaluate();
					Natural right = rhs.Evaluate();

					size_type l_size = result.Size();
					size_type r_size = right.Size();

					for (index_type i = 0; i < r_size; ++i) {

						limb_type left_limb = result[i];
						limb_type right_limb = right[i];

						if (left_limb < right_limb) {
							if (i + 1 < l_size) {
								--result[i + 1];
							}
							left_limb += LIMB_BASE;
						}

						result[i] = left_limb - right_limb;
					}

					result.RemoveLeadingZeroes();
				}

			public:
				NaturalSubtraction(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					Calculate();
				}

				auto Evaluate() const {
					return result;
				}

			};
		}

		template<typename LHS, typename RHS>
		detail::NaturalSubtraction<LHS, RHS> operator-(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			return detail::NaturalSubtraction(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}