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
			};
		}

		using namespace detail;

		template<typename T, typename M>
		MatrixScalarProduct<T, M> operator*(const MatrixExpression<T, M>& vec, const T& c) {
			return MatrixScalarProduct<T, M>(*static_cast<const M*>(&vec), *static_cast<const T*>(&c));
		}

		template<typename T, typename M>
		MatrixScalarProduct<T, M> operator*(const T& c, const MatrixExpression<T, M>& vec) {
			return MatrixScalarProduct<T, M>(*static_cast<const M*>(&vec), *static_cast<const T*>(&c));
		}
	}
}