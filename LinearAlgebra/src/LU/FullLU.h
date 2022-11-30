#pragma once

#include "../Objects/MatrixBase.h"
#include "../Objects/Matrix.h"
#include "../MatrixStructure/SpecialMatrices/SquareOps.h"
#include "LUResult.h"

#include <utility>
namespace MathLib {
	namespace LinearAlgebra {

		namespace implementation {

			namespace LU {
				template<typename T, size_type _Rows, size_type _Columns>
				std::pair<index_type, index_type> FindPivotIndex(const Matrix<T, _Rows, _Columns>& M, const index_type start) {
					std::pair<index_type, index_type> result = std::pair<index_type, index_type>(start, start);
					T max = M.At(start, start);

					for (index_type i = start; i < _Rows; ++i) {
						for (index_type j = start; j < _Columns; ++j) {
							if (M.At(i, j) > max) {
								max = M.At(i, j);
								result.first = i;
								result.second = j;
							}
						}
					}
					return result;
				}

				template<typename T, size_type _Rows, size_type _Columns>
				void PermutePivotRow(FullLUResult<T, _Rows, _Columns>& LU, const index_type row, const index_type pivotIdx) {
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

				template<typename T, size_type _Rows, size_type _Columns>
				void PermutePivotColumn(FullLUResult<T, _Rows, _Columns>& LU, const index_type column, const index_type pivotIdx) {
					if (pivotIdx != column) {

						OPENMP_PARALLELIZE
						for (index_type row = column; row < _Rows; ++row) {
							std::swap(LU.U.At(row, column), LU.U.At(row, pivotIdx));
						}

						LU.Q.Permute(column, pivotIdx);

						OPENMP_PARALLELIZE
						for (index_type row = 0; row < column; ++row) {
							std::swap(LU.L.At(row, column), LU.L.At(row, pivotIdx));
						}
					}
				}
			};

			template<typename T, size_type _Rows, size_type _Columns>
			FullLUResult<T, _Rows, _Columns> DoolittleFull(const Matrix<T, _Rows, _Columns>& M) {
				FullLUResult<T, _Rows, _Columns> LU = FullLUResult<T, _Rows, _Columns>();
				size_type size = std::min(_Rows, _Columns);
				const T one = Identity<T>();

				LU.U = M;

				for (index_type row = 0; row < size; ++row) {

					auto pivot = LU::FindPivotIndex(LU.U, row);
					LU::PermutePivotRow(LU, row, pivot.first);
					LU::PermutePivotColumn(LU, row, pivot.second);

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
		FullLUResult<T, _Rows, _Columns> FullLU(const MatrixBase<T, _Rows, _Columns, Expr>& expr) {
			return implementation::DoolittleFull(expr.Evaluate());
		}

	}
}