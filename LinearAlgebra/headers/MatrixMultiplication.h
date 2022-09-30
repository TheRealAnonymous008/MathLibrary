#include "Matrix.h"

namespace MathLib {
	namespace LinearAlgebra {
		
#ifndef STRASSEN_THRESHOLD
#define STRASSEN_THRESHOLD 10
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

			for (unsigned i = 0; i < M; ++i) {
				for (unsigned j = 0; j < N; ++j) {
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
			
			const unsigned MHalf = M / 2 + M % 2;
			const unsigned PHalf = P / 2 + P % 2;
			const unsigned NHalf = N / 2 + N % 2;
			using ABlock = Matrix<T, MHalf, PHalf>;
			using BBlock = Matrix<T, PHalf, NHalf>;
			using CBlock = Matrix<T, MHalf, NHalf>;

			// A blocks
			ABlock* A11 = A.Slice<MHalf, PHalf>(0, 0);
			ABlock* A12 = A.Slice<MHalf, PHalf>(0, PHalf);
			ABlock* A21 = A.Slice<MHalf, PHalf>(MHalf, 0);
			ABlock* A22 = A.Slice<MHalf, PHalf>(MHalf, PHalf);

			// B blocks
			BBlock* B11 = B.Slice<PHalf, NHalf>(0, 0);
			BBlock* B12 = B.Slice<PHalf, NHalf>(0, NHalf);
			BBlock* B21 = B.Slice<PHalf, NHalf>(PHalf, 0);
			BBlock* B22 = B.Slice<PHalf, NHalf>(PHalf, NHalf);

			CBlock u = MatrixMultiply(	ABlock(*A21 - *A11),		BBlock(*B12 - *B22));
			CBlock v = MatrixMultiply(	ABlock(*A21 + *A22),		BBlock(*B12 - *B11));
			CBlock w = MatrixMultiply(	ABlock(*A21 + *A22 - *A11), BBlock(*B11 + *B22 - *B12));

			// C blocks
			CBlock C11 = CBlock(MatrixMultiply(*A11, *B11) + MatrixMultiply(*A12, *B12));
			CBlock C12 = CBlock(w + u +		MatrixMultiply(*A22 , BBlock(*B21 + *B12 - *B11 - *B22)));
			CBlock C21 = CBlock((w + v +	MatrixMultiply(ABlock(*A11 + *A12 - *A21 - *A22) , *B22)));
			CBlock C22 = CBlock(w + u + v);

			C->AddBlock(0, 0,			C11);
			C->AddBlock(0, NHalf,		C12);
			C->AddBlock(MHalf, 0,		C21);
			C->AddBlock(MHalf, NHalf,	C22);

			return *C;
		}
	}
}