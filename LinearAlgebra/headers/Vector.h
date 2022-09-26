#pragma once

#include "../fwd.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N>
		class Vector : public Array<T, N> {
		public:
			using Array<T, N>::Array;

			using Array<T, N>::operator=;
			using Array<T, N>::operator+;
			using Array<T, N>::operator+=;
			using Array<T, N>::operator-;
			using Array<T, N>::operator-=;

			using Array::operator==;
			using Array::operator!=;

			using Array::At;

			Vector() {

			}

			explicit Vector(const ArrayBase& base) {
				for (int i = 0; i < base.size; ++i) {
					this->body[i] = base[i];
				}
			}

			const T Dot(const Vector& other) const {
				T result = 0;
				for (int i = 0; i < N; ++i) {
					result += body[i] * other[i];
				}
				return result;
			}

			const T SquareNorm() const {
				return this->Dot(*this);
			}

			const T Norm() const {
				return static_cast<T>(std::sqrt(SquareNorm()));
			}
		};
		
	}
}