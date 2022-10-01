#include "pch.h"

using namespace MathLib::LinearAlgebra;

TEST(MatrixInit, BasicInitilizer01) {
	Matrix<int, 2, 3> matrix;
	ASSERT_TRUE(matrix.rows == 2);
	ASSERT_TRUE(matrix.columns == 3);
}
//
//TEST(MatrixInit, BasicInitializer02) {
//	Matrix<int, 100, 100>* matrix = new Matrix<int, 100, 100>();
//
//	for (unsigned int i = 0; i < 100; ++i) {
//		for (unsigned int j = 0; j < 100; ++j) {
//			auto k = matrix->At({ i, j });
//			ASSERT_TRUE(k == 0);
//		}
//	}
//}

TEST(MatrixInit, SquareMatrixInitializer) {
	SquareMatrix<int, 20> matrix;
	ASSERT_TRUE(matrix.rows == matrix.columns);
}

TEST(MatrixInit, InitWithInitializerList) {
	Matrix<int, 3, 4> A = {
		1, 2, 3, 0,
		4, 5, 6, -1,
		7, 8, 9, -2
	};

	ASSERT_TRUE(A.At({ 2, 1 }) == 8);
	ASSERT_TRUE(A.At({ 1, 3 }) == -1);
	ASSERT_TRUE(A.At({ 0, 2}) == 3);
}

TEST(MatrixEquality, Equality) {
	Matrix<int, 3, 4> A;
	Matrix<int, 3, 4> B;
	
	for (unsigned int i = 0; i < 3; ++i) {
		for (unsigned int j = 0; j < 4; ++j) {
			A.At({ i, j }) = i * j;
			B.At({ i, j }) = i * j;
		}
	}

	ASSERT_TRUE(A == B);
	ASSERT_FALSE(A != B);
}

TEST(MatrixInequality, Inequality) {
	Matrix<int, 3, 4> A;
	Matrix<int, 3, 4> B;

	for (unsigned int i = 0; i < 3; ++i) {
		for (unsigned int j = 0; j < 4; ++j) {
			A.At({ i, j }) = i * j;
			B.At({ i, j }) = i * j;
		}
	}

	A.At({ 1,1 }) = -1;

	ASSERT_TRUE(A != B);
	ASSERT_FALSE(A == B);
}

TEST(MatrixTranspose, Transpose1) {
	Matrix<int, 3, 4> A = {
		1, 2, 3, 0	,
		4, 5, 6, -1,
		7, 8, 9, -2
	};

	Matrix<int, 4, 3> B = {
		1, 4, 7,
		2, 5, 8,
		3, 6, 9,
		0, -1, -2
	};

	ASSERT_TRUE(A.Size() == B.Size() && A.Size() == 12);

	ASSERT_TRUE(A.Transpose() == B);
	ASSERT_TRUE(A.Transpose().Transpose() == A);
	ASSERT_TRUE(B.Transpose() == A);
	ASSERT_TRUE(B.Transpose().Transpose() == B);
}

TEST(MatrixOps, Addition) {
	Matrix<int, 3, 4> A = {
		1, 2, 3, 0,
		4, 5, 6, -1,
		7, 8, 9, -2
	};

	Matrix<int, 3, 4> B = {
		-1, 1, 7, 0,
		3, 4, 8, 0,
		2, 0, -10, -4
	};

	Matrix<int, 3, 4> C = {
		0, 3, 10, 0,
		7, 9, 14, -1,
		9, 8, -1, -6
	};

	ASSERT_TRUE(A + B == B + A);
	ASSERT_TRUE(C == B + A);
	ASSERT_TRUE(C - A == B);
}

TEST(MatrixOps, ScalarMultiplication) {
	Matrix<int, 3, 4> A = {
		1, 2, 3, 0,
		4, 5, 6, -1,
		7, 8, 9, -2
	};
	Matrix<int, 3, 4> B = {
		2, 4, 6, 0,
		8, 10, 12, -2,
		14, 16, 18, -4
	};
	
	ASSERT_TRUE(2 * A == A * 2);
	ASSERT_TRUE(2 * A == B);
	ASSERT_TRUE(B / 2 == A);
}

TEST(MatBlock, Blocking) {
	using Matrix100i = SquareMatrix<int, 10>;
	Matrix100i A = {
	1, 0, 0, 4, -1, 2, 3, 0, 2, 0,
	0, 1, 2, -2, 1, 0, 0, 1, -1, 2,
	3, -3, 1, 0, 2, 1, 1, 0, 0, 0,
	0, 0, 0, 1, 1, 0, 0, 0, 1, 0,
	4, 2, -4, 5, 1, 0, -3, 1, 4, 2,
	3, 1, 4, 1, 2, 5, 7, 0, 0, 1,
	2, 7, -2, 1, -1, 1, -1, 0, 2, 3,
	0, 0, 0, 0, 4, -2, -2, -5, 1, 2,
	0, 0, 1, 2, -1, -2, 3, 1, 1, 2,
	5, 6, 1, -6, 9, -1, 0, 0, 1, 0
	};

	auto A1 = A.Slice<5, 5>(0, 0);
	Matrix<int, 5, 5> t_A1 = {
		1, 0, 0, 4, -1,
		0, 1, 2, -2, 1,
		3, -3, 1, 0, 2,
		0, 0, 0, 1, 1,
		4, 2, -4, 5, 1
	};

	ASSERT_TRUE(*A1 == t_A1);

	auto A2 = A.Slice<4, 3>(3, 4);
	Matrix<int, 4, 3> t_A2 = {
		1, 0, 0, 
		1, 0, -3,
		2, 5, 7,
		-1, 1, -1
	};

	ASSERT_TRUE(*A2 == t_A2);
}

TEST(MatVecMultiplication, Test1) {
	Matrix<int, 3, 4> A = {
		1, 2, 3, 0,
		4, 5, 6, -1,
		7, 8, 9, -2
	};

	Vector<int, 4> x1 = {	0, 0, 0, 1	};
	Vector<int, 3> y1 = {	0, -1, -2	};

	Vector<int, 4> x2 = {	1, 2, 3, 4	};
	Vector<int, 3> y2 = {	14, 28, 42	};


	ASSERT_TRUE(A * x1 == y1);
	ASSERT_TRUE(A * x2 == y2);

	using Vector4i = Vector<int, 4>;
	ASSERT_TRUE(A * Vector4i(x1 + x2) == y1 + y2);
	ASSERT_TRUE(A * Vector4i(4 * x1) == 4 * y1);
	ASSERT_TRUE(A * Vector4i(2 * x1 - 3 * x2) == 2 * y1 - 3 * y2);
}

TEST(MatVecMultiplication, Test2) {
	using Matrix100i = SquareMatrix<int, 10>;
	Matrix100i A = {
		1, 0, 0, 4, -1, 2, 3, 0, 2, 0,
		0, 1, 2, -2, 1, 0, 0, 1, -1, 2,
		3, -3, 1, 0, 2, 1, 1, 0, 0, 0,
		0, 0, 0, 1, 1, 0, 0, 0, 1, 0,
		4, 2, -4, 5, 1, 0, -3, 1, 4, 2,
		3, 1, 4, 1, 2, 5, 7, 0, 0, 1,
		2, 7, -2, 1, -1, 1, -1, 0, 2, 3,
		0, 0, 0, 0, 4, -2, -2, -5, 1, 2,
		0, 0, 1, 2, -1, -2, 3, 1, 1, 2,
		5, 6, 1, -6, 9, -1, 0, 0, 1, 0
	};

	using Vector10i = Vector<int, 10>;

	Vector10i x1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	Vector10i y1 = { 63, 24, 23, 18, 64, 120, 56, -17, 52, 44 };

	Vector10i x2 = { 1, -1, 2, -2, 3, -3, 4, -4, 5, -5 };
	Vector10i y2 = { 6, -9, 15, 6, -19, 22, -26, 25, 4, 48 };

	ASSERT_TRUE(A * x1 == y1);
	ASSERT_TRUE(A * x2 == y2);
	ASSERT_TRUE(A * Vector10i(5*x1 - 7*x2) == 5*y1 - 7*y2);
	ASSERT_TRUE(A * Vector10i(-17*x1 + 13*x2) == -17*y1 + 13*y2);
	ASSERT_TRUE(A * Vector10i(301*x1 + 404*x2) == Matrix100i(301 * A) * x1 + Matrix100i(404 * A) * x2);
}

TEST(MatMatMultiplication, Test1) {
	using Matrix4x4i = Matrix<int, 4, 4>;
	using Matrix3x3i = Matrix<int, 3, 3>;

	Matrix<int, 4, 4> A = {
		1, 2, 3, 0,
		4, 5, 6, -1,
		7, 8, 9, -2,
		-3, -4, 0, 0
	};

	Matrix4x4i AT = A.Transpose();

	ASSERT_TRUE(MatrixMultiply(A, AT)== Matrix4x4i({
		14, 32, 50, -11,
		32, 78, 124, -32,
		50, 124, 198, -53,
		-11, -32, -53, 25
	}));


	ASSERT_TRUE(MatrixMultiply(AT, A) == Matrix4x4i({
		75, 90, 90, -18,
		90, 109, 108, -21,
		90, 108, 126, -24,
		-18, -21, -24, 5
	}));
}

TEST(MatMatMultiplication, Test2) {
	using Matrix4x3i = Matrix<int, 4, 3>;
	using Matrix3x4i = Matrix<int, 3, 4>;

	using Matrix4x4i = Matrix<int, 4, 4>;
	using Matrix3x3i = Matrix<int, 3, 3>;

	Matrix<int, 4, 3> A = {
		1, 2, 4, 
		-1, 0, 1,
		-3, 5, 2,
		7, -11, 8
	};

	Matrix<int, 3, 4> B = {
		0, -4, 3, 2,
		7, -2, 1, 1,
		-2, 8, 13, 5
	};

	ASSERT_TRUE(MatrixMultiply(A, B) == Matrix4x4i({
		6, 24, 57, 24,
		-2, 12, 10, 3,
		31, 18, 22, 9,
		-93, 58, 114, 43
	}));

	ASSERT_TRUE(MatrixMultiply(B, A) == Matrix3x3i({
		9, -7, 18,
		13, 8, 36,
		-14, 6, 66
	}));
}

TEST(MatMatMultiplication, Strassen1) {
	using Matrix4x4i = Matrix<int, 4, 4>;
	using Matrix3x3i = Matrix<int, 3, 3>;

	Matrix<int, 4, 4> A = {
		1, 2, 3, 0,
		4, 5, 6, -1,
		7, 8, 9, -2,
		-3, -4, 0, 0
	};

	Matrix4x4i AT = A.Transpose();

	ASSERT_TRUE(StrassenMatMul(A, AT) == Matrix4x4i({
		14, 32, 50, -11,
		32, 78, 124, -32,
		50, 124, 198, -53,
		-11, -32, -53, 25
		}));


	ASSERT_TRUE(StrassenMatMul(AT, A) == Matrix4x4i({
		75, 90, 90, -18,
		90, 109, 108, -21,
		90, 108, 126, -24,
		-18, -21, -24, 5
		}));
}

TEST(MatMatMultiplication, Strassen2) {
	const unsigned N = 100;
	auto *A = new Matrix<int, N, N>();
	auto *B = new Matrix<int, N, N>();

	for (unsigned i = 0; i < N; ++i) {
		for (unsigned j = 0; j < N; ++j) {
			A->At({ i, j }) = i + j;
			B->At({ i, j }) = j - i;
		}
	}

	auto C = StrassenMatMul(*A, *B);

	int t1 = 0;
	for (unsigned k = 0; k < N; ++k) {
		t1 += A->At({ 3, k }) * B->At({ k, 4 });
	}

	ASSERT_TRUE(t1 == C.At({ 3, 4 }));
}