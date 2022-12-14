#pragma once

#include "../../Exceptions.h"

#include "../Objects/VectorBase.h"
#include "../Objects/Vector.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, size_type N, typename V>
			class VectorScalarProduct : public VectorBase<T, N, 
				VectorScalarProduct<T, N, V>> {
			private:
				const V& vec;
				const T& c;

			public:
				VectorScalarProduct(const V& vec, const T& c) : vec(vec), c(c) {

				}

				T operator[](const index_type& i) const {
					return vec[i] * c;
				}

				auto Evaluate() const{

					Vector<T, N> result;

					OPENMP_PARALLELIZE
					for (index_type i = 0; i < N; ++i) {
						result[i] = vec[i] * c;
					}

					return result;
				}
			};
		}

		

		template<typename T,size_type N, typename V>
		detail::VectorScalarProduct<T, N, V> operator*(
			const VectorBase<T, N, V>& vec, 
			const T& c) 
		{
			return detail::VectorScalarProduct<T, N, V>(*static_cast<const V*>(&vec), *static_cast<const T*>(&c));
		}

		template<typename T, size_type N, typename V>
		detail::VectorScalarProduct<T, N, V> operator*(
			const T& c, 
			const VectorBase<T, N, V>& vec) 
		{
			return detail::VectorScalarProduct<T, N, V>(*static_cast<const V*>(&vec), *static_cast<const T*>(&c));
		}
	}
}