#pragma once

#include "fwd.h"
#include "SquareOps.h"

#include <vector>

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N>
		class PermutationMatrix : public SquareMatrixBase<T, N,
			PermutationMatrix<T, N>> {
		private:
			std::vector<T>* body = new std::vector<T>(N);

		public:
			PermutationMatrix() {
				for (unsigned i = 0; i < N; ++i) {
					(*body)[i] = i;
				}
			}

			const PermutationMatrix& Permute(unsigned x, unsigned y) {
				(*body)[x] = y;
				(*body)[y] = x;

				return *this;
			}

			constexpr unsigned Rows() const {
				return N;
			}

			constexpr unsigned Columns() const {
				return N;
			}

			T At(unsigned i, unsigned j) const {
				return ((*body)[i] != j) ? T() : Identity<T>();
			}

			auto Evaluate() const {
				SquareMatrix<T, N> result;
				for (unsigned i = 0; i < N; ++i) {
					result.At(i, (*body)[i]) = Identity<T>();
				}

				return result;
			}
		};

		template<typename T, const unsigned N, typename Expr>
		const SquareMatrixBase<T, N, Expr>& operator*(
			const SquareMatrixBase<T, N, Expr>& lhs,
			const PermutationMatrix<T, N>& rhs)
		{
			return lhs;
		}
	}
}