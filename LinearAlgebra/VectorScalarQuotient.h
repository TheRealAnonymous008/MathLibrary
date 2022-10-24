#pragma once
#include "fwd.h"
#include "Exceptions.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, typename V>
			class VectorScalarQuotient : public VectorExpression<T, VectorScalarQuotient<T, V>> {
			private:
				const V& vec;
				const T& c;

			public:
				VectorScalarQuotient(const V& vec, const T& c) : vec(vec), c(c) {
					if (c == 0) {
						throw DivisionByZero();
					}
				}

				T operator[](const unsigned& i) const {
					return vec[i] / c;
				}

				unsigned Size() const {
					return  vec.Size();
				}
			};
		}

		using namespace detail;

		template<typename T, typename V>
		VectorScalarQuotient<T, V> operator/(const VectorExpression<T, V>& vec, const T& c) {
			return VectorScalarQuotient<T, V>(*static_cast<const V*>(&vec), *static_cast<const T*>(&c));
		}

	}
}