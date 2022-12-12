#pragma once

#include "../../Exceptions.h"

#include "Natural.h"
#include "NaturalOrder.h"

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

					result = lhs;

					for (index_type i = 0; i < rhs.Size(); ++i) {

						limb_type left_digit = result[i];
						limb_type right_digit = rhs[i];

						if (left_digit < right_digit) {
							if (i + 1 < lhs.Size()) {
								--result[i + 1];
							}
							left_digit += LIMB_BASE;
						}

						result[i] = left_digit - right_digit;
					}

					result.RemoveLeadingZeroes();
				}

			public:
				NaturalSubtraction(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
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
		detail::NaturalSubtraction<LHS, RHS> operator-(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			return detail::NaturalSubtraction(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}