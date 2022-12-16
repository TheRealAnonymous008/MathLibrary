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

		template<typename T, size_type N>
		class PermutationMatrix : public SquareMatrixBase<T, N,
			PermutationMatrix<T, N>> {
		private:
			std::vector<index_type>* body = new std::vector<index_type>(N);

			bool IsPremutation(const std::vector<index_type>& list) {
				std::set<index_type> set;
				for (index_type x : list) {
					if (x < 0 || x >= N) {
						return false;
					}
					set.insert(x);
				}

				return set.size() == N;
			}

		public:
			PermutationMatrix() {
				for (index_type i = 0; i < N; ++i) {
					(*body)[i] = i;
				}
			}

			~PermutationMatrix() {
				delete body;
			}

			PermutationMatrix(const std::vector<index_type>& list) {
				if (!IsPremutation(list)) {
					throw DimensionError();
				}

				for (index_type i = 0; i < N; ++i) {
					(*body)[i] = list[i];
				}
			}

			PermutationMatrix& Permute(index_type x, index_type y) {

				std::swap((*body)[x], (*body)[y]);

				return *this;
			}

			const index_type Map(index_type x)  const{
				return (*body)[x];
			}

			constexpr size_type Rows() const {
				return N;
			}

			constexpr size_type Columns() const {
				return N;
			}

			T At(index_type i, index_type j) const {

				return ((*body)[i] != j) ? T() : Identity<T>();
			}

			auto Evaluate() const {
				SquareMatrix<T, N> result;
				for (index_type i = 0; i < N; ++i) {
					result.At(i, (*body)[i]) = Identity<T>();
				}

				return result;
			}
		};
	}
}