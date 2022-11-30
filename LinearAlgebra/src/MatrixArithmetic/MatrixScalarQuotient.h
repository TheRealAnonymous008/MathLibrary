#pragma once

#include "../../Exceptions.h"

#include "../Objects/Matrix.h"
#include "../Objects/MatrixBase.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, size_type _Rows, size_type _Columns, typename M>
			class MatrixScalarQuotient : public MatrixBase<T, _Rows, _Columns,
				MatrixScalarQuotient<T, _Rows, _Columns, M>> {
			private:
				const M& mat;
				const T& k;

			public:
				MatrixScalarQuotient(const M& mat, const T& k) : mat(mat), k(k) {
					if (k == 0) {
						throw DivisionByZero();
					}
				}

				T At(const index_type& r, const index_type& c) const {
					return  mat.At(r, c) / k;
				}

				constexpr size_type Rows() const {
					return  _Rows;
				}

				constexpr size_type Columns() const {
					return  _Columns;
				}

				auto Evaluate() const{

					Matrix<T, _Rows, _Columns> result;

					OPENMP_PARALLELIZE
					for (index_type i = 0; i < _Rows; ++i) {
						for (index_type j = 0; j < _Columns; ++j) {
							result.At(i, j) = mat.At(i, j) / k;
						}
					}

					return result;
				}
			};
		}

		template<typename T, size_type _Rows, size_type _Columns, typename M>
		detail::MatrixScalarQuotient<T, _Rows, _Columns, M> operator/(
			const MatrixBase<T, _Rows, _Columns, M>& vec, 
			const T& c) 
		{
			return detail::MatrixScalarQuotient<T, _Rows, _Columns, M>(*static_cast<const M*>(&vec), *static_cast<const T*>(&c));
		}
	}
}