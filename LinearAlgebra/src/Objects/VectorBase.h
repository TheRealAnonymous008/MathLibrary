#pragma once

#include "../../headers/Fwd.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, size_type N, typename Derived>
		class VectorBase {
		public:
			T operator[](const index_type& i) const {
				return  static_cast<Derived const&>(*this)[i];
			}

			constexpr size_type Size() const {
				return  N;
			}

			auto Evaluate() const{
				return static_cast<Derived const&>(*this).Evaluate();
			}
		};

		template<
			typename T, 
			size_type N,
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

			for (index_type i = 0; i < lhs.Size(); ++i) {
				if (left[i] != right[i])
					return false;
			}
			return true;
		}

		template<
			typename T, 
			size_type N,
			typename LHS, typename RHS
		>
		bool operator!=(const VectorBase<T, N, LHS>& lhs, const VectorBase<T, N, RHS>& rhs) {
			if (lhs.Size() != rhs.Size())
				return false;

			auto left = lhs.Evaluate();
			auto right = rhs.Evaluate();

			for (index_type i = 0; i < lhs.Size(); ++i) {
				if (left[i] != right[i])
					return true;
			}
			return false;
		}

	}
}