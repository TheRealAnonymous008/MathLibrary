#pragma once


#include "../Objects/VectorBase.h"
#include "../Objects/Vector.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, size_type N>
		class UnitVector : public VectorBase<T, N,
			UnitVector<T, N>> {
		private:
			const index_type& idx;
		public:
			UnitVector(const index_type i) : idx(i) {
				if (idx >= N) {
					throw DimensionError();
				}
			}

			T operator[](const index_type& i) const {
				return (i != idx) ? T() : Identity<T>();
			}

			auto Evaluate() const {

				Vector<T, N> result;

				OPENMP_PARALLELIZE
				for (index_type i = 0; i < N; ++i) {
					result[i] = (*this)[i];
				}

				return result;
			}
		};
	}
}