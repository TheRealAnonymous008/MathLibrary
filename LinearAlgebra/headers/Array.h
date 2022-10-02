#pragma once

#include <functional>
#include <string>
#include "../fwd.h"
#include "ArrayBase.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned ...Ns>
		class Array : public ArrayBase<T, detail::SizeClass<Ns...>::Size()> {
		protected:
			ArrayShape* shape = new ArrayShape({Ns...});
			T sentinel = T();

		public:
			using ArrayBase::ArrayBase;
			using ArrayBase::operator=;
			using ArrayBase::operator+;
			using ArrayBase::operator+=;
			using ArrayBase::operator-;
			using ArrayBase::operator-=;
			using ArrayBase::operator*;
			using ArrayBase::operator*=;
			using ArrayBase::operator/;
			using ArrayBase::operator/=;

			using ArrayBase::operator==;
			using ArrayBase::operator!=;
			
			Array() {

			}

			explicit Array(const ArrayBase& base) {
				for (int i = 0; i < base.size; ++i) {
					this->body[i] = base[i];
				}
			}

			Array(Array* other) {
				if (this == other)
					return;
				for (unsigned i = 0; i < other->size; ++i) {
					this->body[i] = other->At({ i });
				}
			}

			const T& At(std::initializer_list<const unsigned> list) const {
				const int i = shape->Index(list);
				if (i == OUT_OF_SHAPE) {
					return sentinel;
				}
				return body[i];
			}

			T& At(std::initializer_list<const unsigned> list) {
				const int i = shape->Index(list);
				if (i == OUT_OF_SHAPE) {
					return sentinel;
				}
				return body[i];
			}

			template <const unsigned ... Xs>
			void Reshape() {
				if (detail::SizeClass<Xs...>::Size() != size) {
					throw MathLib::Exceptions::InvalidTensorReshape();
				}
				shape = new ArrayShape({ Xs... });
			}

			void Slice(std::initializer_list<const unsigned> lower, std::initializer_list<const unsigned> upper) {
				shape->Slice(lower, upper);
			}

			const unsigned Rank() const {
				return shape->Rank();
			}

			const Array& operator*(const T& c) const {
				Array* result = new Array();

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {
					(*result)[i] = this->body[i] * c;
				}

				return *result;
			}

			friend const Array& operator*(T c, Array v) {
				return v * c;
			}

			const Array& operator/(const T& c) const {
				if (c == 0) {
					throw Exceptions::DivideByZero();
				}

				Array* result = new Array();

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {
					(*result)[i] = this->body[i] / c;
				}

				return *result;
			}

			void operator*=(const T& c) {

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {
					body[i] *= c;
				}
			}

			void operator/=(const T& c) {
				if (c == 0) {
					throw Exceptions::DivideByZero();
				}

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {
					body[i] /= c;
				}
			}

			
		};
	}
}