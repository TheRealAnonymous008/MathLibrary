#pragma once
#include "fwd.h"
#include "Exceptions.h"

namespace MathLib {
	namespace LinearAlgebra {

		namespace detail {
			template<typename T, const unsigned N, typename V>
			class VectorNegation : public VectorExpression<T, N, 
				VectorNegation<T, N, V>> {
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
				
				auto Evaluate() const{

					Vector<T, N> result;

					for (unsigned i = 0; i < Size(); ++i) {
						result[i] = -vec[i];
					}

					return result;
				}
			};
		}

		

		template<
			typename T, 
			const unsigned N, 
			typename V
		>
		detail::VectorNegation<T, N, V> operator-(
			const VectorExpression<T, N, V>& vec) 
		{
			return detail::VectorNegation<T, N, V>(*static_cast<const V*>(&vec));
		}

	}
}