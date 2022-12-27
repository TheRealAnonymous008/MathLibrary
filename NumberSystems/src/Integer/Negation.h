#pragma once

#include "Integer.h"
#include "Complement.h"
#include "Ordering.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename Expr>
			class IntegerNegation : public IntegerBase<IntegerNegation<Expr>> {
			private:
				const Expr& expr;

				Integer result;

				void Calculate() {
					Integer eval = expr.Evaluate();
					result = Integer(NegateSign(eval.Sign()), eval.Magnitude());
				}


			public:
				IntegerNegation(const Expr& expr) : expr(expr) {
					Calculate();
				}

				auto Evaluate() const {
					return result;
				}

			};
		}

		template<typename Expr>
		detail::IntegerNegation<Expr> operator-(const IntegerBase<Expr>& expr) {
			return detail::IntegerNegation(*static_cast<const Expr*>(&expr));
		}

	}
}