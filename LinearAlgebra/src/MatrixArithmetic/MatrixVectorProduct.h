#pragma once

#include "../../Exceptions.h"

#include "../Objects/Matrix.h"
#include "../Objects/MatrixBase.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, size_type M, size_type K, size_type N, typename LHS, typename RHS>
			class MatrixVectorProduct : public VectorBase<T, M,
				MatrixVectorProduct<T, M, K, N, LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;


			public:
				MatrixVectorProduct(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					if (lhs.Columns() != rhs.Size()) {
						throw InvalidTensorProduct();
					}
				}

				T operator[](const index_type& i) const {
					T sum = T();

					for (index_type k = 0; k < rhs.Size(); ++k) {
						sum += lhs.At(i, k) * rhs[k];
					}
					return sum;
				}

				constexpr size_type Size() const {
					return M;
				}


				auto Evaluate() const{
					Vector<T, M> result;

					OPENMP_PARALLELIZE
					for (index_type i = 0; i < M; ++i) {
						for (index_type k = 0; k < N; ++k) {
							result[i] += lhs.At(i, k) * rhs[k];
						}
					}

					return result;
				}
			};
		}

		

		template<typename T, size_type M, size_type K, size_type N, typename LHS, typename RHS>

		detail::MatrixVectorProduct<T, M, K, N, LHS, RHS> operator*(
			const MatrixBase<T, M, K, LHS>& lhs, 
			const VectorBase<T, N, RHS>& rhs) 
		{
			return detail::MatrixVectorProduct<T, M, K, N, LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}