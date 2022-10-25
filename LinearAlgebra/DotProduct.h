#pragma once
#include "fwd.h"
#include "Exceptions.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N, typename LHS, typename RHS>
		T Dot(
			const VectorExpression<T, N, LHS>& lhs, 
			const VectorExpression<T, N, RHS>& rhs) {
			if (lhs.Size() != rhs.Size())
				throw InvalidBinaryOperation();

			T dot = 0;
			for (unsigned i = 0; i < lhs.Size(); ++i) {
				dot += lhs[i] * rhs[i];
			}
			return dot;
		}
	}
}