#pragma once

#include "Natural.h"

namespace MathLib {
	namespace NumberSystems {

		template<typename LHS, typename RHS>
		bool operator==(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			if (lhs.Size() != rhs.Size()) {
				return false;
			}

			size_type size = lhs.Size();

			OPENMP_PARALLELIZE
			for (index_type i = 0; i < size; ++i) {
				if (lhs[i] != rhs[i])
					return false;
			}

			return true;
		}

		template<typename LHS, typename RHS>
		bool operator!=(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			if (lhs.Size() != rhs.Size()) {
				return true;
			}

			size_type size = lhs.Size();

			OPENMP_PARALLELIZE
			for (index_type i = 0; i < size; ++i) {
				if (lhs[i] != rhs[i])
					return true;
			}

			return false;
		}

		template<typename LHS, typename RHS>
		bool operator>(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			size_type l_size = lhs.Size();
			size_type r_size = rhs.Size();

			if (l_size < r_size) {
				return false;
			}
			else if (l_size > r_size) {
				return true;
			}

			size_type size = l_size;

			for (index_type i = size - 1; i < size; --i) {
				if (lhs[i] > rhs[i])
					return true;
				else if (lhs[i] < rhs[i]) {
					return false;
				}
			}
			return false;
		}

		template<typename LHS, typename RHS>
		bool operator<(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			size_type l_size = lhs.Size();
			size_type r_size = rhs.Size();

			if (l_size > r_size) {
				return false;
			}
			else if (l_size < r_size) {
				return true;
			}

			size_type size = r_size;

			for (index_type i = size - 1; i < size; --i) {
				if (lhs[i] < rhs[i])
					return true;
				else if (lhs[i] > rhs[i]) {
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