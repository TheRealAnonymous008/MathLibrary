#pragma once

#include <functional>
#include <string>
#include "../fwd.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N>
		class Array : public Stringable{
		protected:
			ArrayShape shape = ArrayShape(N);			
			const unsigned int size = N;
			T body[N] = {};

		public:
			Array() {

			}

			~Array() {

			}

			const unsigned int Size() const {
				return size;
			}

			ArrayShape Shape() const {
				return shape;
			}

			const unsigned int Rank() const {
				return shape.Rank();
			}

			Array(std::initializer_list<T> list) {
				int i = 0;
				for (auto itr = list.begin(); itr != list.end(); ++itr) {
					body[i] = *itr;
					++i;
				}
			}

			void operator=(const std::initializer_list<T>& list) {
				int i = 0;
				for (auto itr = list.begin(); itr != list.end(); ++itr) {
					body[i] = *itr;
					++i;
				}
			}

			void operator=(const Array& other) {
				for (int i = 0; i < N; ++i) {
					body[i] = other[i];
				}
			}

			const T& operator[](int i) const {
				if (i < 0 || i >= N || shape.Rank() > 1) {
					throw Exceptions::InvalidTensorAccess();
				}
				return body[i];
			}

			T& operator[](int i) {
				if (i < 0 || i >= N || shape.Rank() > 1) {
					throw Exceptions::InvalidTensorAccess();
				}
				return body[i];
			}

			const T& At(std::initializer_list<const unsigned int> shape_list) const {
				ArrayShape target = ArrayShape(shape_list);
				const unsigned int i = shape.GetTargetIndex(target);
				return body[i];
			}			
			
			T& At(std::initializer_list<const unsigned int> shape_list) {
				ArrayShape target = ArrayShape(shape_list);
				const unsigned int i = shape.GetTargetIndex(target);
				return body[i];
			}

			void Reshape(std::initializer_list<const unsigned int> shape_list) {
				shape = ArrayShape(shape_list);
			}

			const bool operator==(const Array& other) const noexcept{

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < N; ++i) {
					if (other[i] != this->body[i])
						return false;
				}
				return true;
			}

			const bool operator!=(const Array& other) const noexcept{

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < N; ++i) {
					if (other[i] != this->body[i])
						return true;
				}
				return false;
			}

			const Array& operator+(const Array& other) const {
				Array<T, N>* result = new Array<T, N>();

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < N; ++i) {
					(*result)[i] = this->body[i] + other[i];
				}

				return *result;
			}
			const Array& operator-(const Array& other) const {
				Array<T, N>* result = new Array<T, N>();

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < N; ++i) {
					(*result)[i] = this->body[i] - other[i];
				}

				return *result;
			}

			const Array& operator*(const Array& other) const {
				Array<T, N>* result = new Array<T, N>();

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < N; ++i) {
					(*result)[i] = this->body[i] * other[i];
				}

				return *result;
			}

			const Array& operator/(const Array& other) const {
				Array<T, N>* result = new Array<T, N>();

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < N; ++i) {
					if (other[i] == 0) {
						throw Exceptions::DivideByZero();
					}

					(*result)[i] = this->body[i] / other[i];
				}

				return *result;
			}

			void operator+=(const Array& other) {

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < N; ++i) {
					body[i] += other[i];
				}
			}

			void operator-=(const Array& other) {

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < N; ++i) {
					body[i] -= other[i];
				}
			}

			void operator*=(const Array& other) {

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < N; ++i) {
					body[i] *= other[i];
				}
			}

			void operator/=(const Array& other) {

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < N; ++i) {
					body[i] /= other[i];
				}
			}

			const Array& Map(const std::function< T(T)>& lambda) {
				Array<T, N>* result = new Array<T, N>();

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < N; ++i) {
					(*result)[i] = lambda(body[i]);
				}

				return *result;
			}
			void MapInplace(const std::function< T(T)>& lambda) {

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < N; ++i) {
					body[i] = lambda(body[i]);
				}
			}

			std::string ToString() override {
				std::string result = "";

				for (int i = 0; i < N - 1; ++i) {
					result += Stringify(body[i]) + " ";
				}
				if (N - 1 >= 0)
					result += Stringify(body[N - 1]);

				result += "\n";
				return result;
			}
		};
	}
}