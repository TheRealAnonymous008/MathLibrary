#include "Matrix.h"

namespace MathLib {
	namespace LinearAlgebra {
		
#ifndef STRASSEN_THRESHOLD
#define STRASSEN_THRESHOLD 256
#endif STRASSEN_THRESHOLD

		template<typename T, const unsigned M, const unsigned P, const unsigned N>
		const Matrix<T, M, N> MatrixMultiply(const Matrix<T, M, P>& A, const Matrix<T, P, N>& B) {
			if (M >= STRASSEN_THRESHOLD || N >= STRASSEN_THRESHOLD || P >= STRASSEN_THRESHOLD)
				return StrassenMatMul(A, B);
			return ClassicMatMul(A, B);
		}


		template<typename T, const unsigned M, const unsigned P, const unsigned N>
		const Matrix<T, M, N>& ClassicMatMul(const Matrix<T, M, P>& A, const Matrix<T, P, N>& B) {
			Matrix<T, M, N>* C = new Matrix<T, M, N>();

#pragma loop(hint_parallel(PARALLEL_THREADS))
			for (unsigned i = 0; i < M; ++i) {

#pragma loop(hint_parallel(PARALLEL_THREADS))
				for (unsigned j = 0; j < N; ++j) {

#pragma loop(hint_parallel(PARALLEL_THREADS))
					for (unsigned k = 0; k < P; ++k) {
						C->At({ i, j }) += A.At({ i, k }) * B.At({ k, j });
					}
				}
			}

			return *C;
		}

		template<typename T, const unsigned M, const unsigned P, const unsigned N>
		const Matrix<T, M, N>& StrassenMatMul(const Matrix<T, M, P>& A, const Matrix<T, P, N>& B) {
			Matrix<T, M, N>* C = new Matrix<T, M, N>();

;			const unsigned MHalf = M / 2 + M % 2;
			const unsigned PHalf = P / 2 + P % 2;
			const unsigned NHalf = N / 2 + N % 2;
			using ABlock = Matrix<T, MHalf, PHalf>;
			using BBlock = Matrix<T, PHalf, NHalf>;
			using CBlock = Matrix<T, MHalf, NHalf>;

			// A blocks
			const ABlock& A11 = A.Slice<MHalf, PHalf>(0, 0);
			const ABlock& A12 = A.Slice<MHalf, PHalf>(0, PHalf);
			const ABlock& A21 = A.Slice<MHalf, PHalf>(MHalf, 0);
			const ABlock& A22 = A.Slice<MHalf, PHalf>(MHalf, PHalf);

			// B blocks
			const BBlock& B11 = B.Slice<PHalf, NHalf>(0, 0);
			const BBlock& B12 = B.Slice<PHalf, NHalf>(0, NHalf);
			const BBlock& B21 = B.Slice<PHalf, NHalf>(PHalf, 0);
			const BBlock& B22 = B.Slice<PHalf, NHalf>(PHalf, NHalf);

			// Helpers
			const auto& x = A21 + A22;

			const auto& u = MatrixMultiply(A21 - A11, B12 - B22);
			const auto& v = MatrixMultiply(x, B12 - B11);
			const auto& z = MatrixMultiply(A11, B11);
			const auto& w = z + MatrixMultiply(x - A11, B11 + B22 - B12);

			// C blocks
			const auto& C11 = z + MatrixMultiply(A12, B21);
			C->AddBlock(0, 0, C11);

			const CBlock& C22 = w + u + v;
			C->AddBlock(MHalf, NHalf, C22);

			const CBlock& C21 = w + u + MatrixMultiply(A22, B21 + B12 - B11 - B22);
			C->AddBlock(MHalf, 0, C21);
			
			const CBlock& C12 = w + v + MatrixMultiply(A11 + A12 - A21 - A22, B22);
			C->AddBlock(0, NHalf, C12);

			// Teardown
			delete& x;
			delete& A11; delete& A12; delete& A21; delete& A22;
			delete& B11; delete& B12; delete& B21; delete& B22;
			delete& C11; delete& C12; delete& C21; delete& C22;

			return *C;
		}
	}
}