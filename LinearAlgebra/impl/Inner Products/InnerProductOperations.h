#pragma once
#include "Exceptions.h"

#include "../Objects/VectorBase.h"
#include "StandardInnerProduct.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N, typename E>
		T SquareNorm(const VectorBase<T, N, E>& exp) {
			return Dot(exp, exp);
		}

		template<typename T, const unsigned N, typename E>
		T Norm(const VectorBase<T, N, E>& exp) {
			T norm = std::sqrt(Dot(exp, exp));
			return norm;
		}

		template<typename T, const unsigned N, typename E>
		Vector<T, N> Normalize(const VectorBase<T, N, E>& expr)
		{
			return expr / Norm(expr);
		}
		
		template<typename T, const unsigned N, typename E>
		bool IsNormal(const VectorBase<T, N, E>& exp){
			return Norm(exp) == Identity<T>();
		}

	}
}