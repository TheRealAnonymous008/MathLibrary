#pragma once

#include "../fwd.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N>
		class Vector : public Array<T, N> {
		public:
			using Array<T, N>::Array;

			using Array<T, N>::operator=;
			using Array<T, N>::operator+=;
			using Array<T, N>::operator-;
			using Array<T, N>::operator-=;

			using Array::operator==;
			using Array::operator!=;

			using Array::At;

			Vector() {

			}

			const Vector& operator+(const Vector& other) const {
				Vector* result = new Vector();

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {

					result->body[i] = this->body[i] + other.body[i];
				}

				return *result;
			}

			// TODO: Add all vector arithmetic methods here

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