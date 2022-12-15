#pragma once

#include "Natural.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename Expr>
			class NaturalIncrement : public NaturalBase<NaturalIncrement<Expr>> {
			private:
				const Expr& expr;

				Natural result;
				void Calculate() {
					result = expr.Evaluate();
					vector_type digits = result.Digits();
					size_type size = digits.size();

					for (index_type i = 0; i < size; ++i) {
						if (digits[i] == LIMB_BASE - 1) {
							digits[i] = LIMB_BASE - 1;
						}
						else {
							++digits[i];
							break;
						}
					}
				}


			public:
				NaturalIncrement(const Expr& expr) : expr(expr) {
					Calculate();
				}

				auto Evaluate() const {
					return result;
				}

			};
		}

		template<typename Expr>
		detail::NaturalIncrement<Expr> operator++(const NaturalBase<Expr>& expr) {
			return detail::NaturalIncrement(*static_cast<const Expr*>(&expr));
		}

	}
}