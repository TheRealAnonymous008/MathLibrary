#pragma once
#include "fwd.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, const unsigned _Rows, const unsigned _Columns, typename Expr>
			class MatrixTranspose : public MatrixBase<T, _Rows, _Columns, 
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

					OPENMP_PARALLELIZE
					for (unsigned i = 0; i < _Rows; ++i) {
						for (unsigned j = 0; j < _Columns; ++j) {
							result.At(i, j) = expr.At(j, i);
						}
					}

					return result;
				}
			};
		}

		template<typename T, const unsigned _Rows, const unsigned _Columns,  typename Expr>
		detail::MatrixTranspose<T, _Rows, _Columns, Expr> Transpose(
			const MatrixBase<T, _Columns, _Rows, Expr>& expr) 
		{
			return detail::MatrixTranspose<T, _Rows, _Columns, Expr>(*static_cast<const Expr*>(&expr));
		}

	}
}