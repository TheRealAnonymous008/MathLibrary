#pragma once

#include "Natural.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename LHS, typename RHS>
			class NaturalAddition : public NaturalBase<NaturalAddition<LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				vector_type result;

				const vector_type Calculate() const {
					const size_type size = std::max(lhs.Size(), rhs.Size());
					const size_type minsize = std::min(lhs.Size(), rhs.Size());

					vector_type digits = vector_type(size);

					auto lvec = lhs.Digits();
					auto rvec = rhs.Digits();
					data_type carry = 0;

					for (index_type i = 0; i < minsize; ++i) {
						digits[i] = lvec[i] + rvec[i] + carry;

						carry = digits[i] / DIGIT_BASE;
						digits[i] = digits[i] % DIGIT_BASE;
					}

					for (index_type i = minsize; i < lhs.Size(); ++i) {
						digits[i] = lvec[i] + carry;
						carry = digits[i] / DIGIT_BASE;
						digits[i] = digits[i] % DIGIT_BASE;
					}

					for (index_type i = minsize; i < rhs.Size(); ++i) {
						digits[i] = rvec[i] + carry;
						carry = digits[i] / DIGIT_BASE;
						digits[i] = digits[i] % DIGIT_BASE;
					}

					return digits;
				}


			public: 
				NaturalAddition(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					this->result = Calculate();
					
				}

				const vector_type Digits() const {
					return result;
				}

				auto Evaluate() const {
					return Natural(result);
				}

			};
		}

		template<typename LHS, typename RHS>
		detail::NaturalAddition<LHS, RHS> operator+(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			return detail::NaturalAddition(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}