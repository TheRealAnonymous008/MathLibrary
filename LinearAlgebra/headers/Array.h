#pragma once

#include <functional>
#include <string>
#include "../fwd.h"
#include "ArrayBase.h"
#include "ArrayOps.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned ...Ns>
		class Array : public ArrayBase<T, detail::SizeClass<Ns...>::Size()> {
		protected:
			ArrayShape shape = ArrayShape({Ns...});
			T sentinel = T();

		public:
			using ArrayBase::ArrayBase;
			using ArrayBase::operator=;
			using ArrayBase::operator+=;
			using ArrayBase::operator-=;
			using ArrayBase::operator*=;
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
				const int i = shape.Index(list);
				if (i == OUT_OF_SHAPE) {
					return sentinel;
				}
				return body[i];
			}

			T& At(std::initializer_list<const unsigned> list) {
				const int i = shape.Index(list);
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
				shape = ArrayShape({ Xs... });
			}

			void Slice(std::initializer_list<const unsigned> lower, std::initializer_list<const unsigned> upper) {
				shape.Slice(lower, upper);
			}

			const unsigned Rank() const {
				return shape.Rank();
			}

			const Array& operator+(const Array& other) const {
				return ArrayAddition<T, Ns...>(*this, other).Get();
			}

			const Array& operator-(const Array& other) const {
				return ArraySubtraction<T, Ns...>(*this, other).Get();
			}

			const Array& operator*(const Array& other) const {
				return ArrayMultiplication<T, Ns...>(*this, other).Get();
			}

			const Array& operator/(const Array& other) const {
				return ArrayDivision<T, Ns...>(*this, other).Get();
			}

			const Array& operator*(const T& c) const {
				return ArrayScalarProduct<T, Ns...>(*this, c).Get();
			}

			friend const Array& operator*(T c, Array v) {
				return v * c;
			}

			const Array& operator/(const T& c) const {
				return ArrayScalarQuotient<T, Ns...>(*this, c).Get();
			}

			const Array& operator*=(const T& c) {

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {

					body[i] *= c;
				}
				return *this;
			}

			const Array& operator/=(const T& c) {
				if (c == 0) {
					throw Exceptions::DivideByZero();
				}

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (int i = 0; i < size; ++i) {

					body[i] /= c;
				}

				return *this;
			}

			
		};
	}
}