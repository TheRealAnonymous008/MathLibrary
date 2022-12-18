#pragma once

#include "IntegerBase.h"
#include "Integer.h"

namespace MathLib {
	namespace NumberSystems {

		template<typename LHS, typename RHS>
		bool operator==(const IntegerBase<LHS>& lhs, const IntegerBase<RHS>& rhs) {
			Integer left = lhs.Evaluate();
			Integer right = rhs.Evaluate();

			if (left.SignedSize() != right.SignedSize()) {
				return false;
			}

			auto size = left.Size();

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

			if (left.SignedSize() != right.SignedSize()) {
				return true;
			}

			auto size = left.Size();

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

			auto l_size = left.SignedSize();
			auto r_size = right.SignedSize();

			if (l_size < r_size) {
				return false;
			}
			else if (l_size > r_size) {
				return true;
			}

			auto size = left.Size();

			for (index_type i = size - 1; i < size; --i) {
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

			auto l_size = left.SignedSize();
			auto r_size = right.SignedSize();

			if (l_size > r_size) {
				return false;
			}
			else if (l_size < r_size) {
				return true;
			}

			auto size = right.Size();

			for (index_type i = size - 1; i < size; --i) {
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