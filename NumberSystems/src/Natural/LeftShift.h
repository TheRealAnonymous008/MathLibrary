#pragma once

#include "Natural.h"
#include "ToULL.h"

#include "../Utils/FitLimbToBase.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class NaturalLeftShift : public NaturalBase<NaturalLeftShift<LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				Natural result;

				void Calculate() {
					Natural left = lhs.Evaluate();

					auto shift = ToULL(rhs);
					auto zeroes = shift / LIMB_BASE_POWER;
					shift = shift % LIMB_BASE_POWER;

					result = left;
					limb_type residue = 0;
					size_type size = left.Size();

					for (index_type i = 0; i < size; ++i) {
						FitLimb buffer = FitLimbToBase((result[i] << shift) + residue);
						result[i] = buffer.value;
						residue = buffer.carry;
					}

					if (residue != 0)
						result.AddMostLimb(residue);

					result.AddTrailingZeros(zeroes);
				}


			public:
				NaturalLeftShift(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					Calculate();

				}

				auto Evaluate() const {
					return result;
				}

			};
		}
		
		template<typename LHS, typename RHS>
		detail::NaturalLeftShift<LHS, RHS> operator<<(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			return detail::NaturalLeftShift(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}