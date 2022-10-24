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

				V* result = nullptr;

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

				V Evaluate() {
					delete result;
					result = new V();

					for (unsigned i = 0; i < Size(); ++i) {
						(*result)[i] = vec[i] / c;
					}

					return *result;
				}
			};
		}

		

		template<typename T, typename V>
		detail::VectorScalarQuotient<T, V> operator/(const VectorExpression<T, V>& vec, const T& c) {
			return detail::VectorScalarQuotient<T, V>(*static_cast<const V*>(&vec), *static_cast<const T*>(&c));
		}

	}
}