#pragma once

#include "IntegerBase.h"
#include "Integer.h"

namespace MathLib {
	namespace NumberSystems {

		template<typename LHS, typename RHS>
		bool operator==(const IntegerBase<LHS>& lhs, const IntegerBase<RHS>& rhs) {
			Integer left = lhs.Evaluate();
			Integer right = rhs.Evaluate();

			if (left.Size() != right.Size() || left.Sign() != right.Sign()) {
				return false;
			}

			auto size = abs(left.Size());

			for (signed_index_type i = 0; i < size; ++i) {
				if (left[i] != right[i])
					return false;
			}

			return true;
		}

		template<typename LHS, typename RHS>
		bool operator!=(const IntegerBase<LHS>& lhs, const IntegerBase<RHS>& rhs) {
			Integer left = lhs.Evaluate();
			Integer right = rhs.Evaluate();

			if (left.Size() != right.Size() || left.Sign() != right.Sign()) {
				return true;
			}

			auto size = abs(left.Size());

			for (signed_index_type i = 0; i < size; ++i) {
				if (left[i] != right[i])
					return true;
			}

			return false;
		}

		template<typename LHS, typename RHS>
		bool operator>(const IntegerBase<LHS>& lhs, const IntegerBase<RHS>& rhs) {
			Integer left = lhs.Evaluate();
			Integer right = rhs.Evaluate();

			auto l_size = left.Size();
			auto r_size = right.Size();

			if (l_size < r_size) {
				return false;
			}
			else if (l_size > r_size) {
				return true;
			}

			auto size = abs(l_size);

			for (signed_index_type i = 0; i < size; ++i) {
				if (left[i] > right[i])
					return true;
				else if (left[i] < right[i]) {
					return false;
				}
			}
			return false;
		}

		template<typename LHS, typename RHS>
		bool operator<(const IntegerBase<LHS>& lhs, const IntegerBase<RHS>& rhs) {
			Integer left = lhs.Evaluate();
			Integer right = rhs.Evaluate();

			auto l_size = left.Size();
			auto r_size = right.Size();

			if (l_size > r_size) {
				return false;
			}
			else if (l_size < r_size) {
				return true;
			}

			auto size = abs(r_size);

			for (signed_index_type i = 0; i < size; ++i) {
				if (left[i] < right[i])
					return true;
				else if (left[i] > right[i]) {
					return false;
				}
			}

			return false;
		}

		template<typename LHS, typename RHS>
		bool operator>=(const IntegerBase<LHS>& lhs, const IntegerBase<RHS>& rhs) {
			return lhs > rhs || lhs == rhs;
		}

		template<typename LHS, typename RHS>
		bool operator<=(const IntegerBase<LHS>& lhs, const IntegerBase<RHS>& rhs) {
			return lhs < rhs || lhs == rhs;
		}
	}
}