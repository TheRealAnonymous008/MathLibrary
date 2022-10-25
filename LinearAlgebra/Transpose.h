#pragma once
#include "fwd.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, typename Expr> 
			class MatrixTranspose : public MatrixExpression<T, MatrixTranspose<T, Expr>> {
			private:
				const Expr& expr;

			public:
				MatrixTranspose(const Expr& expr) : expr(expr) {

				}

				T At(const unsigned& r, const unsigned& c) const {
					return  expr.At(c, r);
				}

				constexpr unsigned Rows() const {
					return  expr.Columns();
				}

				constexpr unsigned Columns() const {
					return  expr.Rows();
				}

				template<const unsigned _Rows, const unsigned _Columns>
				Matrix<T, _Rows, _Columns> Evaluate() {

					Matrix<T, _Rows, _Columns> result;

					for (unsigned i = 0; i < Rows(); ++i) {
						for (unsigned j = 0; j < Columns(); ++j) {
							result[i][j] = expr.At(j, i);
						}
					}

					return result;
				}
			};
		}

		template<typename T, typename Expr>
		detail::MatrixTranspose<T, Expr> Transpose(const MatrixExpression<T, Expr>& expr) {
			return detail::MatrixTranspose<T, Expr>(*static_cast<const Expr*>(&expr));
		}

	}
}