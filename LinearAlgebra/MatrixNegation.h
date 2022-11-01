#pragma once
#include "fwd.h"
#include "Exceptions.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, const unsigned _Rows, const unsigned _Columns, typename E>
			class MatrixNegation : public MatrixBase<T, _Rows, _Columns, 
				MatrixNegation<T, _Rows, _Columns, E>> {
			private:
				const E& expr;

			public:
				MatrixNegation(const E& expr) : expr(expr) {

				}

				T At(const unsigned& r, const unsigned& c) const {
					return  -expr.At(r, c);
				}

				constexpr unsigned Rows() const {
					return  _Rows;
				}

				constexpr unsigned Columns() const {
					return  _Columns;
				}

				auto Evaluate() const {

					Matrix<T, _Rows, _Columns> result;

					for (unsigned i = 0; i < Rows(); ++i) {
						for (unsigned j = 0; j < Columns(); ++j) {
							result.At(i, j) = -expr.At(i, j);
						}
					}

					return result;
				}
			};
		}

		template<
			typename T, 
			const unsigned _Rows, const unsigned _Columns, 
			typename E
		>

		detail::MatrixNegation<T, _Rows, _Columns, E> operator-(
			const MatrixBase<T, _Rows, _Columns, E>& expr) 
		{
			return detail::MatrixNegation<T, _Rows, _Columns, E>(*static_cast<const E*>(&expr));
		}

	}
}