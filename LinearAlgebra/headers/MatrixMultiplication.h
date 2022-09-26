#include "Matrix.h"

namespace MathLib {
	namespace LinearAlgebra {
		
		template<typename T, const unsigned M, const unsigned P, const unsigned N>
		const Matrix<T, M, N>& operator*(const Matrix<T, M, P>& A, const Matrix<T, P, N>& B) {
			Matrix<T, M, N> *C = new Matrix<T, M, N>();

			if (M / 2 == 1 || P / 2 == 1 || N / 2==  1)
				return *C;

			Matrix<T, M / 2, P / 2>* a = new Matrix<T, M / 2, P / 2>();
			Matrix<T, P / 2, N / 2>* b = new Matrix<T, P / 2, N / 2>();
			
			Matrix<T, M / 2, N / 2> c = *a * *b;

			return *C;
		}
	}
}