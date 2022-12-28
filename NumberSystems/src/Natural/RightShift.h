#pragma once

#include "Natural.h"
#include "ToULL.h"

#include "../Utils/FitLimbToBase.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class RightShift<Natural, LHS, RHS> : public NaturalBase<RightShift<Natural, LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				Natural result;

				void Calculate() {
					auto shift = ToULL(rhs);
					auto zeroes = shift / LIMB_BASE_POWER;
					shift = shift % LIMB_BASE_POWER;

					result = lhs.Evaluate();
					limb_type residue = 0;

					result.RemoveLeastLimbs(zeroes);
					size_type size = result.Size();

					if (size != 0) {
						for (index_type i = 0; i < size - 1; ++i) {
							limb_type next_bits = result[i + 1] & ((1 << (shift)) - 1);
							result[i] = (result[i] >> shift) + (next_bits << (LIMB_BASE_POWER - shift));
						}

						result[size - 1] >>= shift;
					}

					result.RemoveLeadingZeroes();

				}


			public:
				RightShift<Natural, LHS, RHS>(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					Calculate();

				}

				auto Evaluate() const {
					return result;
				}

			};
		}

		template<typename LHS, typename RHS>
		detail::RightShift<Natural, LHS, RHS> operator>>(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			return detail::RightShift<Natural, LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}