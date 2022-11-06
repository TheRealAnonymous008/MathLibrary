#pragma once

#include "../Objects/MatrixBase.h"
#include "../Objects/Matrix.h"
#include "../Matrix Structure/SquareOps.h"
#include "LUResult.h"

namespace MathLib {
	namespace LinearAlgebra{

		namespace implementation {

			namespace LU {
				template<typename T, const unsigned _Rows, const unsigned _Columns>
				unsigned FindPivotRow(const PermutationMatrix<T, _Rows>& P, const Matrix<T, _Rows, _Columns>& M, const unsigned column) {
					unsigned pivotIdx = column;
					for (unsigned i = column; i < _Rows; ++i) {

						if ((P * M).At(i, column) > (P * M).At(pivotIdx, column)) {
							pivotIdx = i;
						}
					}
					return pivotIdx;
				}
			};

			template<typename T, const unsigned _Rows, const unsigned _Columns>
			PartialLUDecomposition<T, _Rows, _Columns> DoolittleLU(const Matrix<T, _Rows, _Columns>& M) {
				PartialLUDecomposition<T, _Rows, _Columns> LU = PartialLUDecomposition<T, _Rows, _Columns>();
				const unsigned size = std::min(_Rows, _Columns);
				const T one = Identity<T>();

				for (unsigned row = 0; row < size; ++row) {
					
					unsigned pivotIdx = LU::FindPivotRow(LU.P, M, row);
					//LU.P.Permute(row, pivotIdx);

					for (unsigned column = row; column < _Columns; ++column) {
						T sum = T();

						for (unsigned k = 0; k < row; ++k) {
							sum += LU.L.At(row, k) * LU.U.At(k, column);
						}

						LU.U.At(row, column) = (LU.P * M).At(row, column) - sum;
					}


					LU.L.At(row, row) = one;
					for (unsigned j = row + 1; j < _Rows; ++j) {
						T sum = T();

						for (unsigned k = 0; k < row; k++)
							sum += LU.L.At(j, k) * LU.U.At(k, row);

						LU.L.At(j, row) = ((LU.P * M).At(j, row) - sum) * one / LU.U.At(row, row);
					}
				}
				
				return LU;
			}
		}

		template<typename T, const unsigned _Rows, const unsigned _Columns, typename Expr>
		PartialLUDecomposition<T, _Rows, _Columns> PartialLU(MatrixBase<T, _Rows, _Columns, Expr>& expr) {
			return implementation::DoolittleLU(expr.Evaluate());
		}

	}
}