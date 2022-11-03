#pragma once

#include "fwd.h"
#include "SquareOps.h"

#include <vector>

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N>
		class PermutationMatrix : SquareMatrixBase<T, N,
			PermutationMatrix<T, N> {
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

			T At(unsigned i, unsigned j) const {
				return ((*body)[i] != j) ? T() : Identity<T>();
			}
		};

		
	}
}