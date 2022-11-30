#pragma once

#include "../../Objects/MatrixBase.h"
#include "../../Objects/Matrix.h"
#include "SquareOps.h"
#include "../../../Exceptions.h"

#include <vector>
#include <utility>
#include <set>

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N>
		class PermutationMatrix : public SquareMatrixBase<T, N,
			PermutationMatrix<T, N>> {
		private:
			std::vector<unsigned>* body = new std::vector<unsigned>(N);

			bool IsPremutation(const std::vector<unsigned>& list) {
				std::set<unsigned> set;
				for (unsigned x : list) {
					if (x < 0 || x >= N) {
						return false;
					}
					set.insert(x);
				}

				return set.size() == N;
			}

		public:
			PermutationMatrix() {
				for (unsigned i = 0; i < N; ++i) {
					(*body)[i] = i;
				}
			}

			PermutationMatrix(const std::vector<unsigned>& list) {
				if (!IsPremutation(list)) {
					throw DimensionError();
				}

				for (unsigned i = 0; i < N; ++i) {
					(*body)[i] = list[i];
				}
			}

			PermutationMatrix& Permute(unsigned x, unsigned y) {

				std::swap((*body)[x], (*body)[y]);

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