#pragma once

#include "Natural.h"

namespace MathLib {
	namespace NumberSystems {

		template<typename LHS, typename RHS>
		bool operator==(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			Natural left = lhs.Evaluate();
			Natural right = rhs.Evaluate();

			if (left.Size() != right.Size()) {
				return false;
			}

			size_type size = left.Size();

			OPENMP_PARALLELIZE
			for (index_type i = 0; i < size; ++i) {
				if (left[i] != right[i])
					return false;
			}

			return true;
		}

		template<typename LHS, typename RHS>
		bool operator!=(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			Natural left = lhs.Evaluate();
			Natural right = rhs.Evaluate();

			if (left.Size() != right.Size()) {
				return true;
			}

			size_type size = left.Size();

			OPENMP_PARALLELIZE
			for (index_type i = 0; i < size; ++i) {
				if (left[i] != right[i])
					return true;
			}

			return false;
		}

		template<typename LHS, typename RHS>
		bool operator>(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			Natural left = lhs.Evaluate();
			Natural right = rhs.Evaluate();

			size_type l_size = left.Size();
			size_type r_size = right.Size();

			if (l_size < r_size) {
				return false;
			}
			else if (l_size > r_size) {
				return true;
			}

			size_type size = l_size;

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
		bool operator<(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			Natural left = lhs.Evaluate();
			Natural right = rhs.Evaluate();

			size_type l_size = left.Size();
			size_type r_size = right.Size();

			if (l_size > r_size) {
				return false;
			}
			else if (l_size < r_size) {
				return true;
			}

			size_type size = r_size;

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
		bool operator>=(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			return lhs > rhs || lhs == rhs;
		}

		template<typename LHS, typename RHS>
		bool operator<=(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			return lhs < rhs || lhs == rhs;
		}
	}
}