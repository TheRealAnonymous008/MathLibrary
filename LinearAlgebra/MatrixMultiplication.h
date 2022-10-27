#pragma once
#include "fwd.h"
#include "Exceptions.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace implementation {
			template<
				typename T,
				const unsigned _Rows, const unsigned _Inner, const unsigned _Columns,
				typename LHS, typename RHS>

			const Matrix<T, _Rows, _Columns>& MatrixMultiply(
				const MatrixExpression<T, _Rows, _Inner, LHS>& lhs,
				const MatrixExpression<T, _Inner, _Columns, RHS>& rhs
			) {
				return ElementaryMatrixMultiplication(*static_cast<const LHS*>(&lhs), 
					*static_cast<const RHS*>(&rhs));
			}

			template<
				typename T,
				const unsigned _Rows, const unsigned _Inner, const unsigned _Columns,
				typename LHS, typename RHS>

			const Matrix<T, _Rows, _Columns>& ElementaryMatrixMultiplication(
				const MatrixExpression<T, _Rows, _Inner, LHS>& lhs,
				const MatrixExpression<T, _Inner, _Columns, RHS>& rhs
			) {

				Matrix<T, _Rows, _Columns> result;

				for (unsigned i = 0; i < _Rows; ++i) {
					for (unsigned j = 0; j < _Columns; ++j) {
						for (unsigned k = 0; k < _Inner; ++k) {
							result.At(i, j) = lhs.At(i, k) * rhs.At(k, j);
						}
					}
				}

				return result;
			}

		}



		namespace detail {
			template<typename T, const unsigned _Rows, const unsigned _Columns, typename LHS, typename RHS>
			class MatrixMultiplication : public MatrixExpression<T, _Rows, _Columns, 
				MatrixMultiplication<T, _Rows, _Columns, LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

			public:
				MatrixMultiplication(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					if (lhs.Columns() != rhs.Rows()) {
						throw InvalidTensorProduct();
					}
				}

				T At(const unsigned& r, const unsigned& c) const {
					T sum = T();

					for (unsigned k = 0; k < lhs.Columns(); ++k) {
						sum += lhs.At(r, k) * rhs.At(k, c);
					}

					return sum;
				}

				constexpr unsigned Rows() const {
					return  lhs.Rows();
				}

				constexpr unsigned Columns() const {
					return  rhs.Columns();
				}

				auto Evaluate() const {
					return implementation::MatrixMultiply(lhs.Evaluate(), rhs.Evaluate());
				}
			};
		}

		template<
			typename T, 
			const unsigned _Rows, const unsigned _Inner, const unsigned _Columns, 
			typename LHS, typename RHS
		>

		detail::MatrixMultiplication<T, _Rows, _Columns, LHS, RHS> operator*(
			const MatrixExpression<T, _Rows, _Inner, LHS>& lhs, 
			const MatrixExpression<T, _Inner, _Columns, RHS>& rhs) 
		{
			return detail::MatrixMultiplication<T, _Rows, _Columns, LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}
	}
}