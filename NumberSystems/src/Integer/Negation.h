#pragma once

#include "Integer.h"
#include "Complement.h"
#include "Ordering.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename Expr>
			class Negation<Integer, Expr> : public IntegerBase<Negation<Integer, Expr>> {
			private:
				const Expr& expr;

				Integer result;

				void Calculate() {
					Integer eval = expr.Evaluate();
					result = Integer(NegateSign(eval.Sign()), eval.Magnitude());
				}


			public:
				Negation<Integer, Expr>(const Expr& expr) : expr(expr) {
					Calculate();
				}

				auto Evaluate() const {
					return result;
				}

			};
		}

		template<typename Expr>
		detail::Negation<Integer, Expr> operator-(const IntegerBase<Expr>& expr) {
			return detail::Negation<Integer, Expr>(*static_cast<const Expr*>(&expr));
		}

	}
}