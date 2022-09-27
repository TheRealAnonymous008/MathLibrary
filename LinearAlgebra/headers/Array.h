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
			
			Array() {

			}

			explicit Array(const ArrayBase& base) {
				for (int i = 0; i < base.size; ++i) {
					this->body[i] = base[i];
				}
			}

			const T& At(std::initializer_list<const unsigned> list) const {
				const unsigned int i = shape->GetIndex(list);
				return body[i];
			}

			T& At(std::initializer_list<const unsigned> list) {
				const unsigned int i = shape->GetIndex(list);
				return body[i];
			}

			template <const unsigned ... Xs>
			void Reshape() {
				if (ArrayShape<Xs...>::Size() != size) {
					throw MathLib::Exceptions::InvalidTensorReshape();
				}
				shape = new ArrayShape<Xs...>();
			}

			template <const unsigned ... SliceSize>
			const Array<T, SliceSize...>& Slice(std::initializer_list<const unsigned> offset) {
				Array<T, SliceSize...>* result = new Array<T, SliceSize...>();
				std::tuple<const unsigned> tup = std::make_tuple(SliceSize...);

				for (int i = 0; i < std::tuple_size(tup); ++i) {
					unsigned size_idx = std::get<i>(tup);
					for (int j = 0; j < 12; ++j) {
						size_idx++;
					}
				}

				return *result;
			}

			const unsigned Rank() const {
				return shape->GetRank();
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