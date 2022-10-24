#pragma once

#include "fwd.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, typename E>
		class VectorExpression {
		private:

		public:
			T operator[](size_t i) const {
				return  static_cast<E const&>(*this)[i];
			}

			size_t Size() const {
				return  static_cast<E const&>(*this).Size();
			}
		};

		template<typename T, typename LHS, typename RHS>
		bool operator==(const VectorExpression<T, LHS>& lhs, const VectorExpression<T, RHS>& rhs) {
			if (lhs.Size() != rhs.Size())
				return false;

			for (size_t i = 0; i < lhs.Size(); ++i) {
				if (lhs[i] != rhs[i])
					return false;
			}
			return true;
		}

		template<typename T, typename LHS, typename RHS>
		bool operator!=(const VectorExpression<T, LHS>& lhs, const VectorExpression<T, RHS>& rhs) {
			if (lhs.Size() != rhs.Size())
				return false;

			for (size_t i = 0; i < lhs.Size(); ++i) {
				if (lhs[i] != rhs[i])
					return true;
			}
			return false;
		}

	}
}