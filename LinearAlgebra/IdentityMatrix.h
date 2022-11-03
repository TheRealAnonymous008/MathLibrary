#pragma once

#include "fwd.h"
#include "SquareOps.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned N>
		class IdentityMatrix : SquareMatrix<T, N> {
		private:

		public:
			T At(unsigned i, unsigned j) const {
				return (i != j) ? T() : Identity<T>();
			}
		};
	}
}