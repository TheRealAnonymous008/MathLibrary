#pragma once

#include "Natural.h"

namespace MathLib {
	namespace NumberSystems {

		template<typename LHS, typename RHS>
		bool operator==(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			auto lvec = lhs.Digits();
			auto rvec = rhs.Digits();

			if (lvec.size() != rvec.size()) {
				return false;
			}

			size_type size = lvec.size();

			OPENMP_PARALLELIZE
			for (index_type i = 0; i < size; ++i) {
				if (lvec[i] != rvec[i])
					return false;
			}

			return true;
		}

		template<typename LHS, typename RHS>
		bool operator!=(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			auto lvec = lhs.Digits();
			auto rvec = rhs.Digits();

			if (lvec.size() != rvec.size()) {
				return true;
			}

			size_type size = lvec.size();

			OPENMP_PARALLELIZE
			for (index_type i = 0; i < size; ++i) {
				if (lvec[i] != rvec[i])
					return true;
			}

			return false;
		}

		template<typename LHS, typename RHS>
		bool operator>(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			auto lvec = lhs.Digits();
			auto rvec = rhs.Digits();

			if (lvec.size() < rvec.size()) {
				return false;
			}
			else if (lvec.size() > rvec.size()) {
				return true;
			}

			size_type size = lvec.size();

			for (index_type i = size - 1; i >= 0; --i) {
				if (lvec[i] > rvec[i])
					return true;
				else if (lvec[i] < rvec[i]) {
					return false;
				}
			}
			return false;
		}

		template<typename LHS, typename RHS>
		bool operator<(const NaturalBase<LHS>& lhs, const NaturalBase<RHS>& rhs) {
			auto lvec = lhs.Digits();
			auto rvec = rhs.Digits();

			if (lvec.size() > rvec.size()) {
				return false;
			}
			else if (lvec.size() < rvec.size()) {
				return true;
			}

			size_type size = rvec.size();

			for (index_type i = size - 1; i >= 0; --i) {
				if (lvec[i] < rvec[i])
					return true;
				else if (lvec[i] > rvec[i]) {
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