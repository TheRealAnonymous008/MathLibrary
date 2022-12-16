#pragma once

#include "../../Exceptions.h"

#include "../Objects/VectorBase.h"
#include "../Objects/Vector.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, size_type N, typename V>
			class VectorNegation : public VectorBase<T, N, 
				VectorNegation<T, N, V>> {
			private:
				const V& vec;

			public:
				VectorNegation(const V& vec) : vec(vec) {

				}

				T operator[](const index_type& i) const {
					return -vec[i];
				}

				auto Evaluate() const{

					Vector<T, N> result;

					OPENMP_PARALLELIZE
					for (index_type i = 0; i < N; ++i) {
						result[i] = -vec[i];
					}

					return result;
				}
			};
		}

		

		template<typename T, size_type N, typename V>
		detail::VectorNegation<T, N, V> operator-(
			const VectorBase<T, N, V>& vec) 
		{
			return detail::VectorNegation<T, N, V>(*static_cast<const V*>(&vec));
		}

	}
}