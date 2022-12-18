#pragma once

#include "Integer.h"
#include "Complement.h"
#include "Ordering.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename Expr>
			class IntegerNot : public IntegerBase<IntegerNot<Expr>> {
			private:
				const Expr& expr;

				Integer result;

				void Calculate() {
					if (expr == constants::integers::ZERO) {
						result = constants::integers::NEG_ONE;				// Intentional as the regular result is equivalent to -1
						return;
					}
					Integer eval = Complement(expr.Evaluate());

					IntegerSign sign = (eval.Sign() == POSITIVE) ? NEGATIVE : POSITIVE;

					Natural nat = ~eval.Magnitude();

					result = Decomplement(Integer(sign, nat));

				}


			public:
				IntegerNot(const Expr& expr) : expr(expr) {
					Calculate();
				}

				auto Evaluate() const {
					return result;
				}

			};
		}

		template<typename Expr>
		detail::IntegerNot<Expr> operator~(const IntegerBase<Expr>& expr) {
			return detail::IntegerNot(*static_cast<const Expr*>(&expr));
		}

	}
}