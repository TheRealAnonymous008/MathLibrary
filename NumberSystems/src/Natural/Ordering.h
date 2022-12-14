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
			if (lhs.Size() < rhs.Size()) {
				return false;
			}
			else if (lhs.Size() > rhs.Size()) {
				return true;
			}

			size_type size = lhs.Size();

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
			if (lhs.Size() > rhs.Size()) {
				return false;
			}
			else if (lhs.Size() < rhs.Size()) {
				return true;
			}

			size_type size = rhs.Size();

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