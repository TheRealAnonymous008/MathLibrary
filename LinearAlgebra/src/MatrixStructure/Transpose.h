#pragma once

#include "../Objects/MatrixBase.h"
#include "../Objects/Matrix.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, size_type _Rows, size_type _Columns, typename Expr>
			class MatrixTranspose : public MatrixBase<T, _Rows, _Columns, 
				MatrixTranspose<T, _Rows, _Columns, Expr>> 
			{
			private:
				const Expr& expr;

			public:
				MatrixTranspose(const Expr& expr) : expr(expr) {

				}

				T At(const index_type& r, const index_type& c) const {
					return  expr.At(c, r);
				}

				constexpr size_type Rows() const {
					return  expr.Columns();
				}

				constexpr size_type Columns() const {
					return  expr.Rows();
				}

				auto Evaluate() const{

					Matrix<T, _Rows, _Columns> result;

					OPENMP_PARALLELIZE
					for (index_type i = 0; i < _Rows; ++i) {
						for (index_type j = 0; j < _Columns; ++j) {
							result.At(i, j) = expr.At(j, i);
						}
					}

					return result;
				}
			};
		}

		template<typename T, size_type _Rows, size_type _Columns,  typename Expr>
		detail::MatrixTranspose<T, _Rows, _Columns, Expr> Transpose(
			const MatrixBase<T, _Columns, _Rows, Expr>& expr) 
		{
			return detail::MatrixTranspose<T, _Rows, _Columns, Expr>(*static_cast<const Expr*>(&expr));
		}

	}
}