#pragma once

#include "../Objects/MatrixBase.h"
#include "../Objects/Matrix.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, typename Expr, size_type _SliceRows, size_type _SliceColumns>
			class MatrixSlice : public MatrixBase<T, _SliceRows, _SliceColumns,
				MatrixSlice<T, Expr, _SliceRows, _SliceColumns>> {
			private:
				const Expr& expr;
				const index_type& row;
				const index_type& column;

			public:
				MatrixSlice(const Expr& expr, const index_type& row, const index_type& column) : expr(expr) , row(row), column(column) {

				}

				T At(const index_type& r, const index_type& c) const {
					return  expr.At(r + row, c + column);
				}

				auto Evaluate() const {

					Matrix<T, _SliceRows, _SliceColumns> result;

					OPENMP_PARALLELIZE
					for (index_type i = 0; i < _SliceRows; ++i) {
						for (index_type j = 0; j < _SliceColumns; ++j) {
							result.At(i, j) = expr.At(i + row, j + column);
						}
					}

					return result;
				}
			};
		}

		template< size_type _SliceRows, size_type _SliceColumns, size_type _Rows, size_type _Columns, typename T,  typename Expr>
		detail::MatrixSlice<T, Expr, _SliceRows, _SliceColumns> Slice(
			const MatrixBase<T, _Rows, _Columns, Expr>& expr, 
			const index_type row, 
			const index_type column) 
		{
			return detail::MatrixSlice<T, Expr, _SliceRows, _SliceColumns>(
				*static_cast<const Expr*>(&expr), 
				row, column
			);
		}
	}
}