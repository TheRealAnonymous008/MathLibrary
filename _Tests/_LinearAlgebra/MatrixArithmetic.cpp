#include "pch.h"

using namespace MathLib;
using namespace MathLib::LinearAlgebra;

TEST(MatrixInit, MatContructor) {
	Matrix<int, 4, 4> M = Matrix<int, 4, 4>({
		{1, 2, 3, 4}, 
		{5, 6, 7, 8}, 
		{9, 10, 11, 12}, 
		{13, 14, 15, 16} 
	});
	
	ASSERT_EQ(M.At(0, 1), 2);
	ASSERT_EQ(M.At(3, 2), 15);
	ASSERT_EQ(M.At(2, 2), 11);
}

TEST(MatrixInit, MatAssignment) {
	Matrix<int, 4, 4> M = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 16}
	};

	ASSERT_EQ(M.At(0, 1), 2);
	ASSERT_EQ(M.At(3, 2), 15);
	ASSERT_EQ(M.At(2, 2), 11);
}

TEST(MatrixInit, WithExpression) {
	Matrix<int, 4, 4> M = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 16}
	};

	Matrix<int, 4, 4> N = M;

	ASSERT_EQ(M.At(0, 1), N.At(0, 1));
	ASSERT_EQ(M.At(3, 2), N.At(3, 2));
	ASSERT_EQ(M.At(2, 2), N.At(2, 2));
}

TEST(MatrixOperations, Addition) {
	Matrix<int, 4, 4> M = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 16}
	};

	Matrix<int, 4, 4> N = {
		{-1, 2, -3, 0},
		{4, 8, -2, 4},
		{-5, 1, 4, 5},
		{0, 6, -5, 5},
	};

	Matrix<int, 4, 4> P = M + N;

	for (unsigned i = 0; i < 4; ++i) {
		for (unsigned j = 0; j < 4; ++j) {
			ASSERT_EQ(P.At(i, j), M.At(i, j) + N.At(i, j));
		}
	}
}

TEST(MatrixOperations, MultiAdd) {
	Matrix<int, 4, 4> M = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 16}
	};

	Matrix<int, 4, 4> N = {
		{-1, 2, -3, 0},
		{4, 8, -2, 4},
		{-5, 1, 4, 5},
		{0, 6, -5, 5},
	};

	Matrix<int, 4, 4> Q = {
		{-3, 4, 6, 0},
		{-2, 4, -2, -4},
		{-1, 13, 7, 1},
		{7, 12, 0, 0},
	};

	Matrix<int, 4, 4> P = M + N + Q;

	for (unsigned i = 0; i < 4; ++i) {
		for (unsigned j = 0; j < 4; ++j) {
			ASSERT_EQ(P.At(i, j), M.At(i, j) + N.At(i, j) + Q.At(i, j));
		}
	}
}

TEST(MatrixOperations, Subtraction) {
	Matrix<int, 4, 4> M = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 16}
	};

	Matrix<int, 4, 4> N = {
		{-1, 2, -3, 0},
		{4, 8, -2, 4},
		{-5, 1, 4, 5},
		{0, 6, -5, 5},
	};

	Matrix<int, 4, 4> P = M - N;

	for (unsigned i = 0; i < 4; ++i) {
		for (unsigned j = 0; j < 4; ++j) {
			ASSERT_EQ(P.At(i, j), M.At(i, j) - N.At(i, j));
		}
	}
}

TEST(MatrixOperations, Negation) {
	Matrix<int, 4, 4> M = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 16}
	};

	Matrix<int, 4, 4> P = -M;

	for (unsigned i = 0; i < 4; ++i) {
		for (unsigned j = 0; j < 4; ++j) {
			ASSERT_EQ(P.At(i, j), -M.At(i, j));
		}
	}
}

TEST(MatrixOps, BigOps) {
	const unsigned N = 1000;

	Matrix<int, N, N> A = *(new Matrix<int, N, N>());
	Matrix<int, N, N> B = *(new Matrix<int, N, N>());

	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			A.At(i, j) = 2 * i - j;
			B.At(i, j) = 3 * j + 4 * i;
		}
	}

	Matrix<int, N, N> C = A + B;

	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			ASSERT_EQ(C.At(i, j), 6 *i + 2 * j);
		}
	}

}

TEST(MatrixOps, ScalarProduct) {
	Matrix<int, 4, 4> M = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 16}
	};

	Matrix<int, 4, 4> P= 4 * M;

	for (unsigned i = 0; i < 4; ++i) {
		for (unsigned j = 0; j < 4; ++j) {
			ASSERT_EQ(P.At(i, j), 4 * M.At(i, j));
		}
	}
}


TEST(MatrixOps, ScalarQuotient) {
	Matrix<float, 4, 4> M = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 16}
	};

	Matrix<float, 4, 4> P =  M / 3.0f;

	for (unsigned i = 0; i < 4; ++i) {
		for (unsigned j = 0; j < 4; ++j) {
			ASSERT_FLOAT_EQ(P.At(i, j), M.At(i, j) / 3.0f);
		}
	}
}

TEST(MatrixOps, MultiOps) {
	Matrix<int, 4, 4> M = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 16}
	};

	Matrix<int, 4, 4> N = {
		{-1, 2, -3, 0},
		{4, 8, -2, 4},
		{-5, 1, 4, 5},
		{0, 6, -5, 5},
	};

	Matrix<int, 4, 4> P = {
		{-3, 4, 6, 0},
		{-2, 4, -2, -4},
		{-1, 13, 7, 1},
		{7, 12, 0, 0},
	};

	ASSERT_EQ(10 * (M + P), 10 * M + 10 * P);
	ASSERT_EQ((3 * M + 4 * N) + 5 * P, 3 * M + (4 * N + 5 * P));

	Matrix<int, 4, 4> R = -M + 2 * N + P;

	for (unsigned i = 0; i < 4; ++i) {
		for (unsigned j = 0; j < 4; ++j) {
			ASSERT_EQ(R.At(i, j), -M.At(i, j) + 2 * N.At(i, j) + P.At(i, j));
		}
	}
}

TEST(MatrixOps, SelfAssignment) {
	Matrix<int, 4, 4> M = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 16}
	};

	Matrix<int, 4, 4> N = M;
	
	M += N;
	ASSERT_EQ(2 * N, M);

	M -= N;
	ASSERT_EQ(M, N);
}

TEST(MatEager, MatrixEager) {
	Matrix<int, 4, 4> M = {
	{1, 2, 3, 4},
	{5, 6, 7, 8},
	{9, 10, 11, 12},
	{13, 14, 15, 16}
	};

	Matrix<int, 4, 4> N = {
		{-1, 2, -3, 0},
		{4, 8, -2, 4},
		{-5, 1, 4, 5},
		{0, 6, -5, 5},
	};

	Matrix<int, 4, 4> P = (M + N).Evaluate();
	Matrix<int, 4, 4> Q = (M + N).Evaluate() - M;
	Matrix<int, 4, 4> R = (P + Q + M).Evaluate();

	for (unsigned i = 0; i < 4; ++i) {
		for (unsigned j = 0; j < 4; ++j) {
			ASSERT_EQ(P.At(i, j), M.At(i, j) + N.At(i, j));
			ASSERT_EQ(Q.At(i, j), P.At(i, j) - M.At(i, j));
			ASSERT_EQ(R.At(i, j), P.At(i, j) + Q.At(i, j) + M.At(i, j));
		}
	}
}
