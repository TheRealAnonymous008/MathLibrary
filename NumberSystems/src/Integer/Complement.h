#pragma once

#include "Integer.h"

namespace MathLib {
	namespace NumberSystems {

		namespace detail {

			template<typename Expr>
			class IntegerComplement : public IntegerBase<IntegerComplement<Expr>> {
			private:
				const Expr& expr;

				Integer result;

				void Calculate() {
					result = expr.Evaluate();

					if (result.Sign() == NEGATIVE) {
						result = Integer(result.Sign(), (~result.Magnitude()).Evaluate()++);
					}
				}


			public:
				IntegerComplement(const Expr& expr) : expr(expr)  {
					Calculate();
				}

				auto Evaluate() const {
					return result;
				}

			};

			template<typename Expr>
			class IntegerDecomplement : public IntegerBase<IntegerDecomplement<Expr>> {
			private:
				const Expr& expr;

				Integer result;

				void Calculate() {
					result = expr.Evaluate();

					if (result.Sign() == NEGATIVE) {
						result = Integer(result.Sign(), ~(result.Magnitude()--));
					}
				}


			public:
				IntegerDecomplement(const Expr& expr) : expr(expr) {
					Calculate();
				}

				auto Evaluate() const {
					return result;
				}

			};
		}

		template<typename Expr>
		detail::IntegerComplement<Expr> Complement(const IntegerBase<Expr>& expr) {
			return detail::IntegerComplement(*static_cast<const Expr*>(&expr));
		}

		template<typename Expr>
		detail::IntegerDecomplement<Expr> Decomplement(const IntegerBase<Expr>& expr) {
			return detail::IntegerDecomplement(*static_cast<const Expr*>(&expr));
		}
	}
}