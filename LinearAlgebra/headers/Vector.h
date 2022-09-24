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

			using Array::Reshape;

			const Vector& operator*(const T& c) const {
				Vector<T, N>* result = new Vector<T, N>();

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < N; ++i) {
					(*result)[i] = this->body[i] * c;
				}

				return *result;
			}

			friend const Vector<T, N>& operator*(T c, Vector<T, N> v) {
				return v * c;
			}

			const Vector& operator/(const T& c) const {
				if (c == 0) {
					throw Exceptions::DivideByZero();
				}

				Vector<T, N>* result = new Vector<T, N>();

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < N; ++i) {
					(*result)[i] = this->body[i] / c;
				}

				return *result;
			}

			void operator*=(const T& c) {

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < N; ++i) {
					body[i] *= c;
				}
			}

			void operator/=(const T& c) {
				if (c == 0) {
					throw Exceptions::DivideByZero();
				}

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < N; ++i) {
					body[i] /= c;
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