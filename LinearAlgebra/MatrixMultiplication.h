#pragma once
#include "fwd.h"
#include "Exceptions.h"

#define STRASSEN_MATRIX_THRESHOLD 512

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
				if (_Rows > STRASSEN_MATRIX_THRESHOLD || _Columns > STRASSEN_MATRIX_THRESHOLD)
					return StrassenMatrixMultiplication(*static_cast<const LHS*>(&lhs),
						*static_cast<const RHS*>(&rhs));

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

			template<
				typename T,
				const unsigned _Rows, const unsigned _Inner, const unsigned _Columns,
				typename LHS, typename RHS>

			const Matrix<T, _Rows, _Columns>& StrassenMatrixMultiplication(
				const MatrixExpression<T, _Rows, _Inner, LHS>& lhs,
				const MatrixExpression<T, _Inner, _Columns, RHS>& rhs
			) {
				const unsigned halfRow = _Rows / 2 + _Rows % 2;
				const unsigned halfColumn = _Columns / 2 + _Columns% 2;

				auto A11 = PlaceBlock<halfRow, halfColumn>(Slice<halfRow, halfColumn>(lhs, 0, 0));
				auto A12 = PlaceBlock<halfRow, halfColumn>(Slice<halfRow, halfColumn>(lhs, 0, halfColumn));
				auto A21 = PlaceBlock<halfRow, halfColumn>(Slice<halfRow, halfColumn>(lhs, halfRow, 0));
				auto A22 = PlaceBlock<halfRow, halfColumn>(Slice<halfRow, halfColumn>(lhs, halfRow, halfColumn));

				auto B11 = PlaceBlock<halfRow, halfColumn>(Slice<halfRow, halfColumn>(rhs, 0, 0));
				auto B12 = PlaceBlock<halfRow, halfColumn>(Slice<halfRow, halfColumn>(rhs, 0, halfColumn));
				auto B21 = PlaceBlock<halfRow, halfColumn>(Slice<halfRow, halfColumn>(rhs, halfRow, 0));
				auto B22 = PlaceBlock<halfRow, halfColumn>(Slice<halfRow, halfColumn>(rhs, halfRow, halfColumn));

				auto S1 = A21 + A22;
				auto S2 = S1 - A11;
				auto S3 = A11 - A21;
				auto S4 = A12 - S2;

				auto T1 = B12 - B11;
				auto T2 = B22 - T1;
				auto T3 = B22 - B12;
				auto T4 = T2 - B21;

				auto R1 = MatrixMultiply(A11, B11);
				auto R2 = MatrixMultiply(A12, B21);
				auto R3 = MatrixMultiply(S4, B22);
				auto R4 = MatrixMultiply(A22, T4);
				auto R5 = MatrixMultiply(S1, T1);
				auto R6 = MatrixMultiply(S2, T2);
				auto R7 = MatrixMultiply(S3, T3);

				auto C1 = R1 + R2;
				auto C2 = R1 + R6;
				auto C3 = C2 + R7;
				auto C4 = C2 + R5;
				auto C5 = C4 + R3;
				auto C6 = C3 + R4;
				auto C7 = R3 + R5;

				return lhs.Evaluate();
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