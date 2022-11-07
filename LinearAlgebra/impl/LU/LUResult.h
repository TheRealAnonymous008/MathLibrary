#pragma once

#include "../Objects/Matrix.h"
#include "../Matrix Structure/SquareOps.h"
#include "../Matrix Structure/PermutationMatrix.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, const unsigned _Rows, const unsigned _Columns>
		struct PartialLUResult {
			PermutationMatrix<T, _Rows> P;
			SquareMatrix<T, _Rows> L;
			Matrix<T, _Rows, _Columns> U;

			void Log() const {
				std::cout << "P = " << "\n";
				P.Evaluate().Log();

				std::cout << "L = " << "\n";
				L.Log();

				std::cout << "U = " << "\n";
				U.Log();
				std::cout << "\n";
			}
		};
	}
}