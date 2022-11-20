#pragma once


#include "../Objects/VectorBase.h"
#include "../Objects/Vector.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned Idx, const unsigned N>
		class UnitVector : public VectorBase<T, N,
			UnitVector<T, Idx, N>> {
		public:
			UnitVector() {
				if (Idx >= N) {
					throw DimensionError();
				}
			}

			T operator[](const unsigned& i) const {
				return (i != Idx) ? T() : Identity<T>();
			}

			constexpr unsigned Size() const {
				return N;
			}

			auto Evaluate() const {

				Vector<T, N> result;

				OPENMP_PARALLELIZE
				for (unsigned i = 0; i < N; ++i) {
					result[i] = (*this)[i];
				}

				return result;
			}
		};
	}
}