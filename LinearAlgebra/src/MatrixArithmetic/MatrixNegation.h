#pragma once

#include "../../Exceptions.h"

#include "../Objects/Matrix.h"
#include "../Objects/MatrixBase.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, size_type _Rows, size_type _Columns, typename E>
			class MatrixNegation : public MatrixBase<T, _Rows, _Columns, 
				MatrixNegation<T, _Rows, _Columns, E>> {
			private:
				const E& expr;

			public:
				MatrixNegation(const E& expr) : expr(expr) {

				}

				T At(const index_type& r, const index_type& c) const {
					return  -expr.At(r, c);
				}

				auto Evaluate() const {

					Matrix<T, _Rows, _Columns> result;

					OPENMP_PARALLELIZE
					for (index_type i = 0; i < _Rows; ++i) {
						for (index_type j = 0; j < _Columns; ++j) {
							result.At(i, j) = -expr.At(i, j);
						}
					}

					return result;
				}
			};
		}

		template< typename T, size_type _Rows, size_type _Columns, typename E>
		detail::MatrixNegation<T, _Rows, _Columns, E> operator-(
			const MatrixBase<T, _Rows, _Columns, E>& expr) 
		{
			return detail::MatrixNegation<T, _Rows, _Columns, E>(*static_cast<const E*>(&expr));
		}

	}
}