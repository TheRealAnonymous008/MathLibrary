#pragma once

#include <functional>
#include <string>
#include "../fwd.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned ...Ns>
		class Array : public Stringable{
		protected:
			static const unsigned size = ArrayShape<Ns...>::Size();
			ArrayShape<Ns...> shape = ArrayShape<Ns...>();
			T body[size] = {};

		public:
			Array() {

			}

			~Array() {

			}

			static constexpr unsigned Size() {
				return size;
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
				for (int i = 0; i < size; ++i) {
					body[i] = other.body[i];
				}
			}

			const T& operator[](int i) const {
				if (i < 0 || i >= size || shape.Rank() != 1) {
					throw Exceptions::InvalidTensorAccess();
				}
				return body[i];
			}

			T& operator[](int i) {
				if (i < 0 || i >= size || shape.Rank() != 1) {
					throw Exceptions::InvalidTensorAccess();
				}
				return body[i];
			}

			const T& At(std::initializer_list<const unsigned> list) const {
				const unsigned int i = shape.Index(list);
				return body[i];
			}			
			
			T& At(std::initializer_list<const unsigned> list) {
				const unsigned int i = shape.Index(list);
				return body[i];
			}

			const bool operator==(const Array& other) const noexcept{

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {
					if (other.body[i] != this->body[i])
						return false;
				}
				return true;
			}

			const bool operator!=(const Array& other) const noexcept{

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {
					if (other.body[i] != this->body[i])
						return true;
				}
				return false;
			}

			const Array& operator+(const Array& other) const {
				Array<T, Ns...>* result = new Array<T, Ns...>();

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {
					result->body[i] = this->body[i] + other.body[i];
				}

				return *result;
			}
			const Array& operator-(const Array& other) const {
				Array<T, Ns...>* result = new Array<T, Ns...>();

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {
					result->body[i] = this->body[i] - other.body[i];
				}

				return *result;
			}

			const Array& operator*(const Array& other) const {
				Array<T, Ns...>* result = new Array<T, Ns...>();

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {
					result->body[i] = this->body[i] * other.body[i];
				}

				return *result;
			}

			const Array& operator/(const Array& other) const {
				Array<T, Ns...>* result = new Array<T, Ns...>();

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {
					if (other[i] == 0) {
						throw Exceptions::DivideByZero();
					}

					result->body[i] = this->body[i] / other.body[i];
				}

				return *result;
			}

			void operator+=(const Array& other) {

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {
					body[i] += other.body[i];
				}
			}

			void operator-=(const Array& other) {

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {
					body[i] -= other.body[i];
				}
			}

			void operator*=(const Array& other) {

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {
					body[i] *= other.body[i];
				}
			}

			void operator/=(const Array& other) {

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {
					body[i] /= other.body[i];
				}
			}

			const Array& Map(const std::function< T(T)>& lambda) {
				Array<T, Ns...>* result = new Array<T, Ns...>();

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {
					(*result)[i] = lambda(body[i]);
				}

				return *result;
			}
			void MapInplace(const std::function< T(T)>& lambda) {

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {
					body[i] = lambda(body[i]);
				}
			}

			std::string ToString() override {
				std::string result = "";

				for (int i = 0; i < size - 1; ++i) {
					result += Stringify(body[i]) + " ";
				}
				if (size - 1 >= 0)
					result += Stringify(body[size - 1]);

				result += "\n";
				return result;
			}
		};
	}
}