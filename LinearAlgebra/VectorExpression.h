#pragma once

#include "fwd.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, typename E>
		class VectorExpression {
		private:

		protected:
			std::vector<T> body;
			bool isEvaluated = false;

		public:
			T operator[](const unsigned& i) const {
				return  static_cast<E const&>(*this)[i];
			}

			constexpr unsigned Size() const {
				return  static_cast<E const&>(*this).Size();
			}

			const VectorExpression& Evaluate(){
				if (isEvaluated)
					return static_cast<E const&>(*this);

				isEvaluated = true;
				return static_cast<E const&>(*this).Evaluate<Result>();
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