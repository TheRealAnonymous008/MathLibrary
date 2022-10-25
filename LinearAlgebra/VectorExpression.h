#pragma once

#include "fwd.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N, typename E>
		class VectorExpression {
		public:
			T operator[](const unsigned& i) const {
				return  static_cast<E const&>(*this)[i];
			}

			constexpr unsigned Size() const {
				return  static_cast<E const&>(*this).Size();
			}

			auto Evaluate() const{
				return static_cast<E const&>(*this).Evaluate();
			}
		};

		template<
			typename T, 
			const unsigned N,
			typename LHS, typename RHS
		>
		bool operator==(
			const VectorExpression<T, N, LHS>& lhs, 
			const VectorExpression<T, N, RHS>& rhs) 
		{
			if (lhs.Size() != rhs.Size())
				return false;

			for (unsigned i = 0; i < lhs.Size(); ++i) {
				if (lhs[i] != rhs[i])
					return false;
			}
			return true;
		}

		template<
			typename T, 
			const unsigned N,
			typename LHS, typename RHS
		>
		bool operator!=(const VectorExpression<T, N, LHS>& lhs, const VectorExpression<T, N, RHS>& rhs) {
			if (lhs.Size() != rhs.Size())
				return false;

			for (unsigned i = 0; i < lhs.Size(); ++i) {
				if (lhs[i] != rhs[i])
					return true;
			}
			return false;
		}

	}
}