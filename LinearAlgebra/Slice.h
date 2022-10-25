#pragma once
#include "fwd.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, typename Expr, const unsigned _SliceRows, const unsigned _SliceColumns>
			class MatrixSlice : public MatrixExpression<T, _SliceRows, _SliceColumns,
				MatrixSlice<T, Expr, _SliceRows, _SliceColumns>> {
			private:
				const Expr& expr;
				const unsigned& row;
				const unsigned& column;

			public:
				MatrixSlice(const Expr& expr, const unsigned& row, const unsigned& column) : expr(expr) , row(row), column(column) {

				}

				T At(const unsigned& r, const unsigned& c) const {
					return  expr.At(r + row, c + column);
				}

				constexpr unsigned Rows() const {
					return  _SliceRows;
				}

				constexpr unsigned Columns() const {
					return _SliceColumns;
				}

				auto Evaluate() const {

					Matrix<T, _SliceRows, _SliceColumns> result;

					for (unsigned i = 0; i < Rows(); ++i) {
						for (unsigned j = 0; j < Columns(); ++j) {
							result[i][j] = expr.At(i + row, j + column);
						}
					}

					return result;
				}
			};
		}

		template< 
			const unsigned _SliceRows, const unsigned _SliceColumns, 
			const unsigned _Rows, const unsigned _Columns,
			typename T, 
			typename Expr
		>

		detail::MatrixSlice<T, Expr, _SliceRows, _SliceColumns> Slice(
			const MatrixExpression<T, _Rows, _Columns, Expr>& expr, 
			const unsigned row, 
			const unsigned column) 
		{
			return detail::MatrixSlice<T, Expr, _SliceRows, _SliceColumns>(
				*static_cast<const Expr*>(&expr), 
				row, column
			);
		}
	}
}