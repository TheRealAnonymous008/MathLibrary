#pragma once
#include "fwd.h"
#include "Exceptions.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, const unsigned M, const unsigned K, const unsigned N, typename LHS, typename RHS>
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

				T operator[](const unsigned& i) const {
					T sum = T();

					for (unsigned k = 0; k < rhs.Size(); ++k) {
						sum += lhs.At(i, k) * rhs[k];
					}
					return sum;
				}

				constexpr unsigned Size() const {
					return M;
				}


				auto Evaluate() const{
					Vector<T, M> result;

					for (unsigned i = 0; i < Size(); ++i) {
						for (unsigned k = 0; k < rhs.Size(); ++k) {
							result[i] += lhs.At(i, k) * rhs[k];
						}
					}

					return result;
				}
			};
		}

		

		template<typename T, const unsigned M, const unsigned K, const unsigned N, typename LHS, typename RHS>

		detail::MatrixVectorProduct<T, M, K, N, LHS, RHS> operator*(
			const MatrixBase<T, M, K, LHS>& lhs, 
			const VectorBase<T, N, RHS>& rhs) 
		{
			return detail::MatrixVectorProduct<T, M, K, N, LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}