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
			ArrayShape<Ns...> shape = ArrayShape<Ns...>();

		public:
			using ArrayBase::ArrayBase;
			using ArrayBase::operator=;
			using ArrayBase::operator+;
			using ArrayBase::operator+=;
			using ArrayBase::operator-;
			using ArrayBase::operator-=;

			using ArrayBase::operator==;
			using ArrayBase::operator!=;

			const T& At(std::initializer_list<const unsigned> list) const {
				const unsigned int i = shape.Index(list);
				return body[i];
			}

			T& At(std::initializer_list<const unsigned> list) {
				const unsigned int i = shape.Index(list);
				return body[i];
			}
		};
	}
}