#pragma once
#include "fwd.h"

#include "Exceptions.h"
#include "PlaceBlock.h"
#include "Slice.h"

#include <omp.h>
#include <future>
#include <thread>

#define STRASSEN_MATRIX_THRESHOLD 1024

namespace MathLib {
	namespace LinearAlgebra {

		namespace implementation {
			template<typename T,const unsigned _Rows, const unsigned _Inner, const unsigned _Columns,typename LHS, typename RHS>
			Matrix<T, _Rows, _Columns> MatrixMultiply(const MatrixBase<T, _Rows, _Inner, LHS>& lhs, const MatrixBase<T, _Inner, _Columns, RHS>& rhs);

			template<typename T,const unsigned _Rows, const unsigned _Inner, const unsigned _Columns,typename LHS, typename RHS>
			Matrix<T, _Rows, _Columns> ElementaryMatrixMultiplication(const MatrixBase<T, _Rows, _Inner, LHS>& lhs,const MatrixBase<T, _Inner, _Columns, RHS>& rhs);
			
			template<typename T, const unsigned _Rows, const unsigned _Inner, const unsigned _Columns, typename LHS, typename RHS>
			Matrix<T, _Rows, _Columns> StrassenMatrixMultiplication(const MatrixBase<T, _Rows, _Inner, LHS>& lhs, const MatrixBase<T, _Inner, _Columns, RHS>& rhs);
		}

		namespace implementation {
			template<typename T,const unsigned _Rows, const unsigned _Inner, const unsigned _Columns, typename LHS, typename RHS>
			Matrix<T, _Rows, _Columns> MatrixMultiply(
				const MatrixBase<T, _Rows, _Inner, LHS>& lhs,
				const MatrixBase<T, _Inner, _Columns, RHS>& rhs
			) {
				if (_Rows > STRASSEN_MATRIX_THRESHOLD || _Columns > STRASSEN_MATRIX_THRESHOLD || _Inner > STRASSEN_MATRIX_THRESHOLD)
					return StrassenMatrixMultiplication(*static_cast<const LHS*>(&lhs),
						*static_cast<const RHS*>(&rhs));

				return ElementaryMatrixMultiplication(*static_cast<const LHS*>(&lhs), 
					*static_cast<const RHS*>(&rhs));
			}

			template<typename T, const unsigned _Rows, const unsigned _Inner, const unsigned _Columns, typename LHS, typename RHS>
			Matrix<T, _Rows, _Columns> ElementaryMatrixMultiplication(
				const MatrixBase<T, _Rows, _Inner, LHS>& lhs,
				const MatrixBase<T, _Inner, _Columns, RHS>& rhs
			) {

				Matrix<T, _Rows, _Columns> result;

				OPENMP_PARALLELIZE
				for (unsigned i = 0; i < _Rows; ++i) {
					for (unsigned k = 0; k < _Inner; ++k) {
						auto l = lhs.At(i, k);
						for (unsigned j = 0; j < _Columns; ++j) {
							result.At(i, j) += l  *rhs.At(k, j);
						}
					}
				}

				return result;
			}
			
			template<typename T, const unsigned _Rows, const unsigned _Inner, const unsigned _Columns, typename LHS, typename RHS >
			Matrix<T, _Rows, _Columns> StrassenMatrixMultiplication(
				const MatrixBase<T, _Rows, _Inner, LHS>& lhs,
				const MatrixBase<T, _Inner, _Columns, RHS>& rhs
			) {
				const unsigned halfRow = _Rows / 2 + _Rows % 2;
				const unsigned halfInner = _Inner / 2 + _Inner% 2;
				const unsigned halfColumn = _Columns / 2 + _Columns% 2;

				using AMatrix = Matrix<T, halfRow, halfInner>;
				using BMatrix = Matrix<T, halfInner, halfColumn>;
				using CMatrix = Matrix<T, halfRow, halfColumn>;

				AMatrix A11 = PlaceBlock<halfRow, halfInner>(Slice<halfRow, halfInner>(lhs, 0, 0));
				AMatrix A12 = PlaceBlock<halfRow, halfInner>(Slice<halfRow, _Inner - halfInner>(lhs, 0, halfInner));
				AMatrix A21 = PlaceBlock<halfRow, halfInner>(Slice<_Rows - halfRow, halfInner>(lhs, halfRow, 0));
				AMatrix A22 = PlaceBlock<halfRow, halfInner>(Slice<_Rows - halfRow, _Inner - halfInner>(lhs, halfRow, halfInner));
				
				BMatrix B11 = PlaceBlock<halfInner, halfColumn>(Slice<halfInner, halfColumn>(rhs, 0, 0));
				BMatrix B12 = PlaceBlock<halfInner, halfColumn>(Slice<halfInner, _Columns - halfColumn>(rhs, 0, halfColumn));
				BMatrix B21 = PlaceBlock<halfInner, halfColumn>(Slice<_Inner -halfInner, halfColumn>(rhs, halfInner, 0));
				BMatrix B22 = PlaceBlock<halfInner, halfColumn>(Slice<_Inner -halfInner, _Columns - halfColumn>(rhs, halfInner, halfColumn));

				AMatrix S1 = A21 + A22;
				AMatrix S2 = S1 - A11;
				AMatrix S3 = A11 - A21;
				AMatrix S4 = A12 - S2;

				BMatrix T1 = B12 - B11;
				BMatrix T2 = B22 - T1;
				BMatrix T3 = B22 - B12;
				BMatrix T4 = T2 - B21;

				CMatrix R1 = MatrixMultiply(A11, B11);
				CMatrix R2 = MatrixMultiply(A12, B21);
				CMatrix R3 = MatrixMultiply(S4, B22);
				CMatrix R4 = MatrixMultiply(A22, T4);
				CMatrix R5 = MatrixMultiply(S1, T1);
				CMatrix R6 = MatrixMultiply(S2, T2);
				CMatrix R7 = MatrixMultiply(S3, T3);

				CMatrix C1 = R1 + R2;
				CMatrix C2 = R1 + R6;
				CMatrix C3 = C2 + R7;
				CMatrix C4 = C2 + R5;
				CMatrix C5 = C4 + R3;
				CMatrix C6 = C3 - R4;
				CMatrix C7 = C3 + R5;


				Matrix<T, _Rows, _Columns> C;

				PlaceBlock(C, C1, 0, 0);
				PlaceBlock(C, C5, 0, _Columns - halfColumn);
				PlaceBlock(C, C6, _Rows - halfRow, 0);
				PlaceBlock(C, C7, _Rows - halfRow, _Columns - halfColumn);
				
				return C;
			}
		}

		namespace detail {

			template<typename T, const unsigned _Rows, const unsigned _Columns, typename LHS, typename RHS >
			class MatrixMultiplication : public MatrixBase<T, _Rows, _Columns, 
				MatrixMultiplication<T, _Rows, _Columns, LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;
				const Matrix<T, _Rows, _Columns>& result;

			public:
				MatrixMultiplication(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs), 
					result(implementation::MatrixMultiply(lhs.Evaluate(), rhs.Evaluate()))
				{
					if (lhs.Columns() != rhs.Rows()) {
						throw InvalidTensorProduct();
					}
				}

				T At(const unsigned& r, const unsigned& c) const {
					return result.At(r, c);
				}

				constexpr unsigned Rows() const {
					return  lhs.Rows();
				}

				constexpr unsigned Columns() const {
					return  rhs.Columns();
				}

				auto Evaluate() const {
					return result;
				}
			};
		}

		template<typename T, const unsigned _Rows, const unsigned _Inner, const unsigned _Columns,  typename LHS, typename RHS>
		detail::MatrixMultiplication<T, _Rows, _Columns, LHS, RHS> operator*(
			const MatrixBase<T, _Rows, _Inner, LHS>& lhs, 
			const MatrixBase<T, _Inner, _Columns, RHS>& rhs) 
		{
			return detail::MatrixMultiplication<T, _Rows, _Columns, LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}
	}
}