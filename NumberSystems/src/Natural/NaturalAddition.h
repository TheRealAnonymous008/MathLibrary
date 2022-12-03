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

			public: 
				NaturalAddition(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					
					const size_type size = std::max(lhs.Size(), rhs.Size());
					const size_type minsize = std::min(lhs.Size(), rhs.Size());

					result = vector_type(size);

					auto lvec = lhs.Digits();
					auto rvec = rhs.Digits();
					data_type carry = 0;

					for (index_type i = 0; i < minsize; ++i) {
						result[i] = lvec[i] + rvec[i] + carry;
						
						carry = result[i] / DIGIT_BASE;
						result[i] = result[i] % DIGIT_BASE;
					}

					for (index_type i = minsize; i < lhs.Size(); ++i) {
						result[i] = lvec[i] + carry;
						carry = result[i] / DIGIT_BASE;
						result[i] = result[i] % DIGIT_BASE;
					}

					for (index_type i = minsize; i < rhs.Size(); ++i) {
						result[i] = rvec[i] + carry;
						carry = result[i] / DIGIT_BASE;
						result[i] = result[i] % DIGIT_BASE;
					}
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
		detail::NaturalAddition<LHS, RHS> operator+(
			const NaturalBase<LHS>& lhs,
			const NaturalBase<RHS>& rhs)
		{
			return detail::NaturalAddition(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}