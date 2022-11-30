#pragma once

#include "../Objects/Matrix.h"
#include "../MatrixStructure/SpecialMatrices/SquareOps.h"
#include "../MatrixStructure/SpecialMatrices/PermutationMatrix.h"

namespace MathLib {
	namespace LinearAlgebra {

		template<typename T, size_type _Rows, size_type _Columns>
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

		template<typename T, size_type _Rows, size_type _Columns>
		struct FullLUResult {
			PermutationMatrix<T, _Rows> P;
			SquareMatrix<T, _Rows> L;
			Matrix<T, _Rows, _Columns> U;
			PermutationMatrix<T, _Columns> Q;

			void Log() const {
				std::cout << "P = " << "\n";
				P.Evaluate().Log();

				std::cout << "L = " << "\n";
				L.Log();

				std::cout << "U = " << "\n";
				U.Log();

				std::cout << "Q = " << "\n";
				Q.Evaluate().Log();

				std::cout << "\n";
			}
		};
	}
}