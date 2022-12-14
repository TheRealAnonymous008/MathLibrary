#pragma once

#include "Natural.h"
#include "../Utils/FitLimbToBase.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class NaturalAddition : public NaturalBase<NaturalAddition<LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				Natural result;

				void Calculate() {

					const size_type l_size = lhs.Size();
					const size_type r_size = rhs.Size();

					const size_type size = std::max(l_size, r_size);
					const size_type minsize = std::min(l_size, r_size);
					limb_type carry = 0;


					for (index_type i = 0; i < minsize; ++i) {
						auto addition = detail::FitLimbToBase(lhs[i] + rhs[i] + carry);
						result.AddMostLimb(addition.value);
						carry = addition.carry;
					}

					for (index_type i = minsize; i < l_size; ++i) {
						auto addition = detail::FitLimbToBase(lhs[i] + carry);
						result.AddMostLimb(addition.value);
						carry = addition.carry;
					}

					for (index_type i = minsize; i < r_size; ++i) {
						auto addition = detail::FitLimbToBase(rhs[i] + carry);
						result.AddMostLimb(addition.value);
						carry = addition.carry;
					}

					if (carry > 0)
						result.AddMostLimb(carry);
				}


			public: 
				NaturalAddition(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
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
		detail::NaturalAddition<LHS, RHS> operator+(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			return detail::NaturalAddition(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}