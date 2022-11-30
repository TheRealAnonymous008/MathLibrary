#pragma once

#include "../../Exceptions.h"

#include "../Objects/VectorBase.h"
#include "../Objects/Vector.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, const unsigned N, typename V>
			class VectorScalarQuotient : public VectorBase<T, N, 
				VectorScalarQuotient<T, N, V>> 
			{
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

				constexpr unsigned Size() const {
					return  vec.Size();
				}

				auto Evaluate() const{

					Vector<T, N> result;

					OPENMP_PARALLELIZE
					for (unsigned i = 0; i < N; ++i) {
						result[i] = vec[i] / c;
					}

					return result;
				}
			};
		}

		

		template<typename T, const unsigned N, typename V>
		detail::VectorScalarQuotient<T, N, V> operator/(
			const VectorBase<T, N, V>& vec, 
			const T& c) 
		{
			return detail::VectorScalarQuotient<T, N, V>(*static_cast<const V*>(&vec), *static_cast<const T*>(&c));
		}

	}
}