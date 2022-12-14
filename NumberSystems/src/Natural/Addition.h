#pragma once

#include "Natural.h"
#include "../Utils/FitLimbToBase.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class Addition<Natural, LHS, RHS> : public NaturalBase<Addition<Natural, LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				Natural result;

				void Calculate() {
					Natural left = lhs.Evaluate();
					Natural right = rhs.Evaluate();

					const size_type l_size = left.Size();
					const size_type r_size = right.Size();

					const size_type size = std::max(l_size, r_size);
					const size_type minsize = std::min(l_size, r_size);
					limb_type carry = 0;

					result.AddTrailingZeros(size);

					for (index_type i = 0; i < minsize; ++i) {
						auto addition = detail::FitLimbToBase(left[i] + right[i] + carry);
						result[i] = addition.value;
						carry = addition.carry;
					}

					for (index_type i = minsize; i < l_size; ++i) {
						auto addition = detail::FitLimbToBase(left[i] + carry);
						result[i] = addition.value;
						carry = addition.carry;
					}

					for (index_type i = minsize; i < r_size; ++i) {
						auto addition = detail::FitLimbToBase(right[i] + carry);
						result[i] = addition.value;
						carry = addition.carry;
					}

					if (carry > 0)
						result.AddMostLimb(carry);
				}


			public: 
				Addition<Natural, LHS, RHS>(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					Calculate();
				}

				auto Evaluate() const {
					return result;
				}

			};
		}

		template<typename LHS, typename RHS>
		detail::Addition<Natural, LHS, RHS> operator+(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			return detail::Addition<Natural, LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}