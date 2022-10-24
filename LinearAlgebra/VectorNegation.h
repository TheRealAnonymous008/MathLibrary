#pragma once
#include "fwd.h"
#include "Exceptions.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, typename V>
			class VectorNegation : public VectorExpression<T, VectorNegation<T, V>> {
			private:
				const V& vec;

			public:
				VectorNegation(const V& vec) : vec(vec) {

				}

				T operator[](const unsigned& i) const {
					return -vec[i];
				}

				constexpr unsigned Size() const {
					return  vec.Size();
				}

				V Evaluate() const{
					V result;

					for (unsigned i = 0; i < Size(); ++i) {
						(result)[i] = -vec[i];
					}

					return result;
				}
			};
		}

		

		template<typename T, typename V>
		detail::VectorNegation<T, V> operator-(const VectorExpression<T, V>& vec) {
			return detail::VectorNegation<T, V>(*static_cast<const V*>(&vec));
		}

	}
}