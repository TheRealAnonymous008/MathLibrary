#pragma once

#include "../fwd.h"
#include <array>

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N>
		class ArrayBase : public Stringable {
		protected:
			static const int size = N;
			std::array<T, size> body = *(new std::array<T, size>());
			ArrayShape* shape = new ArrayShape({ N });

		public:
			ArrayBase() {

			}

			~ArrayBase() {

			}

			static constexpr unsigned Size() {
				return size;
			}

			ArrayBase(const ArrayBase& other) {
				for (int i = 0; i < size; ++i) {
					this->body[i] = other.body[i];
				}
			}

			ArrayBase(std::initializer_list<T> list) {
				int i = 0;
				for (auto itr = list.begin(); itr != list.end(); ++itr) {
					this->body[i] = *itr;
					++i;
				}
			}

			void operator=(const std::initializer_list<T>& list) {
				int i = 0;
				for (auto itr = list.begin(); itr != list.end(); ++itr) {
					this->body[i] = *itr;
					++i;
				}
			}

			void operator=(const ArrayBase& other) {
				for (int i = 0; i < size; ++i) {
					this->body[i] = other.body[i];
				}
			}

			const T& operator[](int i) const {
				if (i < 0 || i >= size) {
					throw Exceptions::InvalidTensorAccess();
				}
				return body[i];
			}

			T& operator[](int i) {
				if (i < 0 || i >= size) {
					throw Exceptions::InvalidTensorAccess();
				}
				return body[i];
			}

			const bool operator==(const ArrayBase& other) const noexcept {

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {
					if (other.body[i] != this->body[i])
						return false;
				}
				return true;
			}

			const bool operator!=(const ArrayBase& other) const noexcept {

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {
					if (other.body[i] != this->body[i])
						return true;
				}
				return false;
			}

			void operator+=(const ArrayBase& other) {

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {
					body[i] += other.body[i];
				}
			}

			void operator-=(const ArrayBase& other) {

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {
					body[i] -= other.body[i];
				}
			}

			void operator*=(const ArrayBase& other) {

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {
					body[i] *= other.body[i];
				}
			}

			void operator/=(const ArrayBase& other) {

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {
					body[i] /= other.body[i];
				}
			}

			const ArrayBase& Map(const std::function< T(T)>& lambda) const {
				ArrayBase* result = new ArrayBase();

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

				for (unsigned i = 0; i < size - 1; ++i) {
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