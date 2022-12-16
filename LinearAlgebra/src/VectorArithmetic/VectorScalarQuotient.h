#pragma once

#include "../../Exceptions.h"

#include "../Objects/VectorBase.h"
#include "../Objects/Vector.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, size_type N, typename V>
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

				T operator[](const index_type& i) const {
					return vec[i] / c;
				}

				auto Evaluate() const{

					Vector<T, N> result;

					OPENMP_PARALLELIZE
					for (index_type i = 0; i < N; ++i) {
						result[i] = vec[i] / c;
					}

					return result;
				}
			};
		}

		

		template<typename T, size_type N, typename V>
		detail::VectorScalarQuotient<T, N, V> operator/(
			const VectorBase<T, N, V>& vec, 
			const T& c) 
		{
			return detail::VectorScalarQuotient<T, N, V>(*static_cast<const V*>(&vec), *static_cast<const T*>(&c));
		}

	}
}