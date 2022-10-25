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
				
				const VectorNegation& Evaluate() {
					body = std::vector<T>(Size());

					for (unsigned i = 0; i < Size(); ++i) {
						(body)[i] = -vec[i];
					}

					return *this;
				}
			};
		}

		

		template<typename T, typename V>
		detail::VectorNegation<T, V> operator-(const VectorExpression<T, V>& vec) {
			return detail::VectorNegation<T, V>(*static_cast<const V*>(&vec));
		}

	}
}