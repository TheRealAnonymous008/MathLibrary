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
			auto& x = A21 + A22;

			const auto& u0 = A21 - A11;
			const auto& u1 = B12 - B22;
			const CBlock* u = new CBlock(MatrixMultiply(	u0,		u1));
			delete& u0; delete& u1;

			const auto& v0 = B12 - B11;
			const CBlock* v = new CBlock(MatrixMultiply(	x,	v0));
			delete& v0;

			const CBlock* z = new CBlock(MatrixMultiply(	A11, B11  ));

			const auto& w0 = x - A11;
			delete & x;

			const auto& w10 = B11 + B22;
			const auto& w1 = w10 - B12;
			delete& w10;

			const CBlock* w2 = new CBlock(MatrixMultiply(w0, w1));
			delete& w0; 
			delete& w1;

			const CBlock& w = *z + *w2;
			delete w2;

			// C blocks
			const auto& C11_m = new CBlock(MatrixMultiply(A12, B21));
			const auto& C11 = *z + *C11_m;
			delete C11_m;
			C->AddBlock(0, 0,			C11);
			delete& C11;	delete z;

			const auto& x0 = w + *u;
			const CBlock& C22 =x0 + *v;
			C->AddBlock(MHalf, NHalf, C22);
			delete& x0;  delete& C22;

			const auto& b0 = B21 + B12;
			const auto& b1 = b0 - B11;
			const auto& b2 = b1 - B22;
			delete& b0;	delete& b1;

			const auto* C21_m = new CBlock(MatrixMultiply(A22, b2));
			const auto& C21_s = w + *u;
			const CBlock& C21 = C21_s + *C21_m;
			C->AddBlock(MHalf, 0, C21);
			delete u;	delete C21_m;
			delete& C21;	delete& b2;		delete& C21_s;
			
			const auto& a0 = A11 + A12;
			const auto& a1 = a0 - A21;
			const auto& a2 = a1 - A22;
			delete& a0;	delete& a1;

			const auto* C12_m = new CBlock(MatrixMultiply(a2, B22));
			const auto& C12_s = w + *v;
			const CBlock& C12 = C12_s +	*C12_m;
			C->AddBlock(0, NHalf,		C12);
			delete v;	delete C12_m;
			delete& C12;	delete& a2;		delete& C12_s;

			delete& A11; delete& A12; delete& A21; delete& A22;
			delete& B11; delete& B12; delete& B21; delete& B22;

			return *C;
		}
	}
}