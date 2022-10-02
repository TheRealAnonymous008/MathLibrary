#pragma once

#include "../fwd.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned Rows, const unsigned Columns>
		class Matrix : public Array<T, Rows, Columns>{
		public:
			const int rows = Rows;
			const int columns = Columns;

			using Array::Array;
			using Array::operator=;
			using Array::operator+;
			using Array::operator+=;
			using Array::operator-;
			using Array::operator-=;

			using Array::operator==;
			using Array::operator!=;

			using Array::operator*;
			using Array::operator*=;
			using Array::operator/;
			using Array::operator/=;

			using Array::At;
			using Array::ToString;
			using Array::Reshape;

			Matrix() {

			}

			explicit Matrix(const ArrayBase& base) {
				for (int i = 0; i < base.size; ++i) {
					this->body[i] = base[i];
				}
			}

			Matrix<T, Columns, Rows> Transpose() const noexcept{
				Matrix<T, Columns, Rows> transpose;

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (unsigned int i = 0; i < Rows; ++i) {
#pragma loop(hint_parallel(PARALLEL_THREADS))
					for (unsigned int j = 0; j < Columns; ++j) {
						transpose.At({ j, i }) = this->At({ i, j });
					}
				}

				return transpose;
			}

			template<const unsigned SliceRows, const unsigned SliceCols>
			const Matrix<T, SliceRows, SliceCols>& Slice(const unsigned rowOffset, const unsigned colOffset) const{
				Matrix<T, SliceRows, SliceCols> *slice = new Matrix<T, SliceRows, SliceCols>();
				
				for (unsigned i = 0; i < SliceRows && i + rowOffset < Rows; ++i) {
					for (unsigned j = 0; j < SliceCols && j + colOffset < Columns; ++j) {
						slice->At({ i, j }) = this->At({ i + rowOffset, j + colOffset });
					}
				}
				return *slice;
			}

			template<const unsigned BlockRows, const unsigned BlockCols>
			void AddBlock(const unsigned rowOffset, const unsigned colOffset, const Matrix<T, BlockRows, BlockCols>& block) {
				for (unsigned i = 0; i < block.rows && i + rowOffset < Rows; ++i) {
					for (unsigned j = 0; j < block.columns && j  + colOffset < Columns; ++j) {
						this->At({ i + rowOffset, j + colOffset }) = block.At({ i, j });
					}
				}
			}

			const Vector<T, Rows>& operator*(Vector<T, Columns> v) {
				Vector<T, Rows>* res = new Vector<T, Rows>();

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (unsigned i = 0; i < Rows; ++i) {
#pragma loop(hint_parallel(PARALLEL_THREADS))
					for (unsigned j = 0; j < Columns; ++j) {
						(*res)[i] += v[j] * this->At({ i, j });
					}
				}
				return *res;
			}


			
		};

		template<typename T, const unsigned N>
		using SquareMatrix = Matrix<T, N, N>;
	}
}