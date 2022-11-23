#pragma once
#include "Exceptions.h"

#include "../Objects/VectorBase.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N, typename LHS, typename RHS>
		T Dot(
			const VectorBase<T, N, LHS>& lhs, 
			const VectorBase<T, N, RHS>& rhs) 
		{
			if (lhs.Size() != rhs.Size())
				throw InvalidBinaryOperation();

			T dot = T();

			for (unsigned i = 0; i < lhs.Size(); ++i) {
				dot += lhs[i] * rhs[i];
			}
			return dot;
		}
	}
}