#pragma once
#include "fwd.h"
#include "Exceptions.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, typename M>
			class MatrixScalarQuotient : public MatrixExpression<T, MatrixScalarQuotient<T, M>> {
			private:
				const M& mat;
				const T& k;

				M* result;

			public:
				MatrixScalarQuotient(const M& mat, const T& k) : mat(mat), k(k) {
					if (k == 0) {
						throw DivisionByZero();
					}
				}

				T At(const unsigned& r, const unsigned& c) const {
					return  mat.At(r, c) / k;
				}

				unsigned Rows() const {
					return  mat.Rows();
				}

				unsigned Columns() const {
					return  mat.Columns();
				}

				M Evaluate() {
					delete result;
					result = new M();

					for (unsigned i = 0; i < Rows(); ++i) {
						for (unsigned j = 0; j < Columns(); ++j) {
							result->At(i, j) = mat.At(i, j) / c;
						}
					}

					return *result;
				}
			};
		}

		template<typename T, typename M>
		detail::MatrixScalarQuotient<T, M> operator/(const MatrixExpression<T, M>& vec, const T& c) {
			return detail::MatrixScalarQuotient<T, M>(*static_cast<const M*>(&vec), *static_cast<const T*>(&c));
		}
	}
}