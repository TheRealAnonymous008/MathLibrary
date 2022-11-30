#pragma once

#include "../Objects/MatrixBase.h"
#include "../Objects/Matrix.h"
#include "../MatrixStructure/SpecialMatrices/SquareOps.h"
#include "LUResult.h"

#include <utility>

namespace MathLib {
	namespace LinearAlgebra{

		namespace implementation {

			namespace LU {
				template<typename T, size_type _Rows, size_type _Columns>
				index_type FindPivotRow(const Matrix<T, _Rows, _Columns>& M, const index_type column) {
					index_type pivotIdx = column;
					T max = M.At(pivotIdx, column);

					for (index_type i = column; i < _Rows; ++i) {

						if (M.At(i, column) > max) {
							pivotIdx = i;
							max = M.At(i, column);
						}
					}
					return pivotIdx;
				}

				template<typename T, size_type _Rows ,size_type _Columns>
				void PermutePivotRow(PartialLUResult<T, _Rows, _Columns>& LU, const index_type row, const index_type pivotIdx) {
					if (pivotIdx != row) {

						OPENMP_PARALLELIZE
						for (index_type column = row; column < _Columns; ++column) {
							std::swap(LU.U.At(row, column), LU.U.At(pivotIdx, column));
						}

						LU.P.Permute(row, pivotIdx);

						OPENMP_PARALLELIZE
						for (index_type column = 0; column < row; ++column) {
							std::swap(LU.L.At(row, column), LU.L.At(pivotIdx, column));
						}
					}
				}
			};

			template<typename T, size_type _Rows, size_type _Columns>
			PartialLUResult<T, _Rows, _Columns> DoolittlePartial(const Matrix<T, _Rows, _Columns>& M) {
				PartialLUResult<T, _Rows, _Columns> LU = PartialLUResult<T, _Rows, _Columns>();
				size_type size = std::min(_Rows, _Columns);
				const T one = Identity<T>();

				LU.U = M;

				for (index_type row = 0; row < size; ++row) {
					
					index_type pivotIdx = LU::FindPivotRow(LU.U, row);
					LU::PermutePivotRow(LU, row, pivotIdx);

					OPENMP_PARALLELIZE
					for (index_type r = row + 1; r < _Rows; ++r) {
						LU.L.At(r, row) = LU.U.At(r, row) / LU.U.At(row, row);
					}

					OPENMP_PARALLELIZE
					for (index_type r = row + 1; r < _Rows; ++r) {
						for (index_type c = row + 1; c < _Columns; ++c) {
							LU.U.At(r, c) -= LU.L.At(r, row) * LU.U.At(row, c);
						}
						LU.U.At(r, row) = T();
					}

					LU.L.At(row, row) = Identity<T>();
				}
				
				return LU;
			}
		}

		template<typename T, size_type _Rows, size_type _Columns, typename Expr>
		PartialLUResult<T, _Rows, _Columns> PartialLU(const MatrixBase<T, _Rows, _Columns, Expr>& expr) {
			return implementation::DoolittlePartial(expr.Evaluate());
		}

	}
}