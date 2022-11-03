#pragma once

#include "fwd.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N, typename Derived>
		class VectorBase {
		public:
			T operator[](const unsigned& i) const {
				return  static_cast<Derived const&>(*this)[i];
			}

			constexpr unsigned Size() const {
				return  static_cast<Derived const&>(*this).Size();
			}

			auto Evaluate() const{
				return static_cast<Derived const&>(*this).Evaluate();
			}
		};

		template<
			typename T, 
			const unsigned N,
			typename LHS, typename RHS
		>
		bool operator==(
			const VectorBase<T, N, LHS>& lhs, 
			const VectorBase<T, N, RHS>& rhs) 
		{
			if (lhs.Size() != rhs.Size())
				return false;
			
			auto left = lhs.Evaluate();
			auto right = rhs.Evaluate();

			for (unsigned i = 0; i < lhs.Size(); ++i) {
				if (left[i] != right[i])
					return false;
			}
			return true;
		}

		template<
			typename T, 
			const unsigned N,
			typename LHS, typename RHS
		>
		bool operator!=(const VectorBase<T, N, LHS>& lhs, const VectorBase<T, N, RHS>& rhs) {
			if (lhs.Size() != rhs.Size())
				return false;

			auto left = lhs.Evaluate();
			auto right = rhs.Evaluate();

			for (unsigned i = 0; i < lhs.Size(); ++i) {
				if (left[i] != right[i])
					return true;
			}
			return false;
		}

	}
}