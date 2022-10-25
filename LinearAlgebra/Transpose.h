#pragma once
#include "fwd.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, const unsigned _Rows, const unsigned _Columns, typename Expr>
			class MatrixTranspose : public MatrixExpression<T, _Rows, _Columns, 
				MatrixTranspose<T, _Rows, _Columns, Expr>> 
			{
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

				auto Evaluate() const{

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

		template<
			typename T,
			const unsigned _Rows, const unsigned _Columns, 
			typename Expr
		>
		detail::MatrixTranspose<T, _Rows, _Columns, Expr> Transpose(
			const MatrixExpression<T, _Rows, _Columns, Expr>& expr) 
		{
			return detail::MatrixTranspose<T, _Rows, _Columns, Expr>(*static_cast<const Expr*>(&expr));
		}

	}
}