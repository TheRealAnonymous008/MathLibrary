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


			public:
				MatrixVectorProduct(const LHS& lhs, const RHS& rhs) : lhs(lhs), rhs(rhs) {
					if (lhs.Columns() != rhs.Size()) {
						throw InvalidTensorProduct();
					}
				}

				T operator[](const unsigned& i) const {
					if (isEvaluated) {
						return body[i];
					}

					T sum = T();

					for (unsigned k = 0; k < rhs.Size(); ++k) {
						sum += lhs.At(i, k) * rhs[k];
					}
					return sum;
				}

				constexpr unsigned Size() const {
					return  lhs.Rows();
				}


				const MatrixVectorProduct& Evaluate() {

					body = std::vector<T>(Size());

					for (unsigned i = 0; i < Size(); ++i) {
						for (unsigned k = 0; k < rhs.Size(); ++k) {
							(body)[i] += lhs.At(i, k) * rhs[k];
						}
					}
					this->isEvaluated = true;
					return *this;
				}
			};
		}

		

		template<typename T, typename LHS, typename RHS>
		detail::MatrixVectorProduct<T, LHS, RHS> operator*(const MatrixExpression<T, LHS>& lhs, const VectorExpression<T, RHS>& rhs) {
			return detail::MatrixVectorProduct<T, LHS, RHS>(*static_cast<const LHS*>(&lhs), *static_cast<const RHS*>(&rhs));
		}

	}
}