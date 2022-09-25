#pragma once

#include <functional>
#include <string>
#include "../fwd.h"
#include "ArrayBase.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned ...Ns>
		class Array : public ArrayBase<T, ArrayShape<Ns...>::Size()> {
		protected:
			ArrayShapeBase* shape = new ArrayShape<Ns...>();

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

			const T& At(std::initializer_list<const unsigned> list) const {
				const unsigned int i = ArrayShape<Ns...>::Index(list);
				return body[i];
			}

			T& At(std::initializer_list<const unsigned> list) {
				const unsigned int i = ArrayShape<Ns...>::Index(list);
				return body[i];
			}

			const unsigned Rank() const {
				return shape->GetRank();
			}

			template <const unsigned ... Xs>
			void Reshape() {
				if (ArrayShape<Xs...>::Size() != size) {
					throw MathLib::Exceptions::InvalidTensorReshape();
				}
				shape = new ArrayShape<Xs...>();

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