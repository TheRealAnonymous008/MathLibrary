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
			std::vector<unsigned>* body = new std::vector<unsigned>(N);

		public:
			PermutationMatrix() {
				for (unsigned i = 0; i < N; ++i) {
					(*body)[i] = i;
				}
			}

			const PermutationMatrix& Permute(unsigned x, unsigned y) {
				unsigned temp = (*body)[x];
				(*body)[x] = (*body)[y];
				(*body)[y] = temp;

				return *this;
			}

			const unsigned Map(unsigned x)  const{
				return (*body)[x];
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
	}
}