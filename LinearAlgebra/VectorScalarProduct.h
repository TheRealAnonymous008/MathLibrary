#pragma once
#include "fwd.h"
#include "Exceptions.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, typename V>
			class VectorScalarProduct : public VectorExpression<T, VectorScalarProduct<T, V>> {
			private:
				const V& vec;
				const T& c;

				V* result = nullptr;

			public:
				VectorScalarProduct(const V& vec, const T& c) : vec(vec), c(c) {

				}

				T operator[](const unsigned& i) const {
					return vec[i] * c;
				}

				unsigned Size() const {
					return  vec.Size();
				}

				V Evaluate() {
					delete result;
					result = new V();

					for (unsigned i = 0; i < Size(); ++i) {
						(*result)[i] = vec[i] * c;
					}

					return *result;
				}
			};
		}

		

		template<typename T, typename V>
		detail::VectorScalarProduct<T, V> operator*(const VectorExpression<T, V>& vec, const T& c) {
			return detail::VectorScalarProduct<T, V>(*static_cast<const V*>(&vec), *static_cast<const T*>(&c));
		}

		template<typename T, typename V>
		detail::VectorScalarProduct<T, V> operator*(const T& c, const VectorExpression<T, V>& vec) {
			return detail::VectorScalarProduct<T, V>(*static_cast<const V*>(&vec), *static_cast<const T*>(&c));
		}
	}
}