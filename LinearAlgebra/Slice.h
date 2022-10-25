#pragma once
#include "fwd.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, typename Expr, const unsigned _Rows, const unsigned _Columns>
			class MatrixSlice : public MatrixExpression<T, MatrixSlice<T, Expr, _Rows, _Columns>> {
			private:
				const Expr& expr;
				const unsigned& row;
				const unsigned& column;

			public:
				MatrixSlice(const Expr& expr, const unsigned& row, const unsigned& column) : expr(expr) , row(row), column(column) {

				}

				T At(const unsigned& r, const unsigned& c) const {
					return  expr.At(r, c);
				}

				constexpr unsigned Rows() const {
					return  _Rows;
				}

				constexpr unsigned Columns() const {
					return _Columns;
				}

				template<const unsigned _Rows, const unsigned _Columns>
				Matrix<T, _Rows, _Columns> Evaluate() const {

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

		template<typename T, typename Expr, const unsigned _Rows, const unsigned _Columns>
		detail::MatrixSlice<T, Expr, _Rows, _Columns> Slice(const Expr& expr, const unsigned& row, const unsigned& column) {
			return detail::MatrixSlice<T, Expr, _Rows, _Columns>(expr, row, column);
		}

	}
}