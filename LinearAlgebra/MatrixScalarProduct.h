#pragma once
#include "fwd.h"
#include "Exceptions.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, typename M>
			class MatrixScalarProduct : public MatrixExpression<T, MatrixScalarProduct<T, M>> {
			private:
				const M& mat;
				const T& k;
				M* result;

			public:
				MatrixScalarProduct(const M& mat, const T& k) : mat(mat), k(k) {

				}

				T At(const unsigned& r, const unsigned& c) const {
					return  mat.At(r, c) * k;
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
							result->At(i, j) = mat.At(i, j) * c;
						}
					}

					return *result;
				}
			};
		}

		

		template<typename T, typename M>
		detail::MatrixScalarProduct<T, M> operator*(const MatrixExpression<T, M>& mat, const T& c) {
			return detail::MatrixScalarProduct<T, M>(*static_cast<const M*>(&mat), *static_cast<const T*>(&c));
		}

		template<typename T, typename M>
		detail::MatrixScalarProduct<T, M> operator*(const T& c, const MatrixExpression<T, M>& mat) {
			return detail::MatrixScalarProduct<T, M>(*static_cast<const M*>(&mat), *static_cast<const T*>(&c));
		}
	}
}