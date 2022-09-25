#pragma once

#include <functional>
#include <string>
#include "../fwd.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N>
		class Array : public Stringable{
		protected:
			static const unsigned size = N;
			T body[N] = {};

		public:
			Array() {

			}

			~Array() {

			}

			static constexpr unsigned Size() {
				return N;
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
				if (i < 0 || i >= N) {
					throw Exceptions::InvalidTensorAccess();
				}
				return body[i];
			}

			T& operator[](int i) {
				if (i < 0 || i >= N) {
					throw Exceptions::InvalidTensorAccess();
				}
				return body[i];
			}

			const T& At(std::initializer_list<const unsigned int> shape_list) const {
				const unsigned int i = shape_list.begin();
				return body[i];
			}			
			
			T& At(std::initializer_list<const unsigned int> shape_list) {
				const unsigned int i = shape_list.begin();
				return body[i];
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

			const Array& Flatten() {
				Array<T, N>* result = new Array<T, N>();
				(*result) = (*this);
				return *result;
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
	
#define UNKNOWN_SIZE -1

		template<typename T, const unsigned N, const unsigned ...Ns>
		class MultiArray : public Array<MultiArray<T, Ns...>, N> {
		protected:
			using Array::body;
			static const unsigned size = N * Array<T, Ns...>::Size();

		public:

			using Array::Array;
			using Array::Map;
			using Array::MapInplace;
			using Array::operator+;
			using Array::operator+=;
			using Array::operator-;
			using Array::operator-=;
			using Array::operator*;
			using Array::operator*=;
			using Array::operator/;
			using Array::operator/=;

			using Array::operator==;
			using Array::operator!=;
			using Array::operator=;
			using Array::operator[];

			constexpr unsigned int Size() {
				return size;
			}
			
			const MultiArray<T, size>& Flatten(){
				MultiArray<T, size> flattened;

				unsigned idx = 0;
				for (unsigned i = 0; i < N; ++i) {
					auto sub = body[i].Flatten();
					for (idx; idx < sub.Size(); ++idx) {
						flattened[idx] = sub[idx];
						++idx;
					}
				}

				return flattened;
			}
			
		};
	
		template<typename T, const unsigned N>
		class MultiArray<T, N> : public Array<T, N>{
		private:

		public:
			using Array::Array;
			using Array::operator=;
			using Array::Flatten;
		};
	}
}