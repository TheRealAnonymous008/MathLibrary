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
					const size_type size = std::max(lhs.Size(), rhs.Size());
					const size_type minsize = std::min(lhs.Size(), rhs.Size());
					limb_type carry = 0;


					for (index_type i = 0; i < minsize; ++i) {
						auto addition = detail::FitLimbToBase(lhs[i] + rhs[i] + carry);
						result.AddMostLimb(addition.value);
						carry = addition.carry;
					}

					for (index_type i = minsize; i < lhs.Size(); ++i) {
						auto addition = detail::FitLimbToBase(lhs[i] + carry);
						result.AddMostLimb(addition.value);
						carry = addition.carry;
					}

					for (index_type i = minsize; i < rhs.Size(); ++i) {
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