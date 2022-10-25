#pragma once

#include "fwd.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, typename E>
		class VectorExpression {
		public:
			T operator[](const unsigned& i) const {
				return  static_cast<E const&>(*this)[i];
			}

			constexpr unsigned Size() const {
				return  static_cast<E const&>(*this).Size();
			}

			template<typename Q = T, const unsigned N>
			Vector<Q, N> Evaluate(){
				return static_cast<E const&>(*this).Evaluate();
			}
		};

		template<typename T, typename LHS, typename RHS>
		bool operator==(const VectorExpression<T, LHS>& lhs, const VectorExpression<T, RHS>& rhs) {
			if (lhs.Size() != rhs.Size())
				return false;

			for (unsigned i = 0; i < lhs.Size(); ++i) {
				if (lhs[i] != rhs[i])
					return false;
			}
			return true;
		}

		template<typename T, typename LHS, typename RHS>
		bool operator!=(const VectorExpression<T, LHS>& lhs, const VectorExpression<T, RHS>& rhs) {
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