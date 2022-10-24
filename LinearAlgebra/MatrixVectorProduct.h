#pragma once
#include "fwd.h"
#include "Exceptions.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, typename LHS, typename RHS>
			class MatrixVectorProduct : public VectorExpression<T, MatrixVectorProduct<T, LHS, RHS>> {
			private:
				const LHS& lhs;
				const RHS& rhs;

				void* result = nullptr;

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

				unsigned Size() const {
					return lhs.Rows();
				}

				template<const unsigned M>
				Vector<T, M> Evaluate() {
					delete result;

					Vector<T, M> *tmp = new Vector<T, M>();

					for (unsigned i = 0; i < Size(); ++i) {
						for (unsigned k = 0; k < rhs.Size(); ++k) {
							(*tmp)[i] += lhs.At(i, k) * rhs[k];
						}
					}

					result = tmp;

					return *tmp;
				}
			};
		}

		

		template<typename T, typename LHS, typename RHS>
		detail::MatrixVectorProduct<T, LHS, RHS> operator*(const MatrixExpression<T, LHS>& lhs, const VectorExpression<T, RHS>& rhs) {
			return detail::MatrixVectorProduct<T, LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}