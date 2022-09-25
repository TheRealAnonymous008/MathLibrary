#include "pch.h"

using namespace MathLib::LinearAlgebra;

TEST(ArrayInit, BasicInitializer) {
	Array<int, 7> test;
	
	ASSERT_TRUE(test.Size() == 7);

	for (int i = 0; i < 6; ++i) {
		ASSERT_TRUE(test[i] == 0);
	}
}

TEST(ArrayInit, NonzeroInitializer) {
	Array<int, 100> test;

	for (int i = 0; i < 100; ++i) {
		test[i] = i * i;
	}

	for (int i = 0; i < 100; ++i) {
		ASSERT_TRUE(test[i] == i * i);
	}
}

TEST(ArrayAccess, InvalidAccess) {
	Array<int, 100> test;

	ASSERT_THROW(test[101] = 1, MathLib::Exceptions::InvalidTensorAccess);
}

TEST(ArrayEquality, Equality) {
	Array<int, 3> A;
	Array<int, 3> B;

	for (int i = 0; i < 3; ++i) {
		A[i] = i * i;
		B[i] = i * A[i];
		A[i] = i * A[i];
	}

	ASSERT_TRUE(A == B);
	ASSERT_FALSE(A != B);
}

TEST(ArrayInequality, Inequality) {
	Array<int, 100> A;
	Array<int, 100> B;

	for (int i = 0; i < 100; ++i) {
		A[i] = i * i;
		B[i] = i * i;
	}

	B[50] = B[50] + 1;

	ASSERT_TRUE(A != B);
	ASSERT_FALSE(A == B);
}

TEST(ArrayOps, Assignment) {
	Array<int, 100> A;
	Array<int, 100> B;

	for (int i = 0; i < 100; ++i) {
		A[i] = 2 * i + 1;
	}

	B = A;

	ASSERT_TRUE(A == B);
}

TEST(ArrayOps, Sum) {
	Array<int, 100> A;
	Array<int, 100> B;
	Array<int, 100> C;

	for (int i = 0; i < 100; ++i) {
		A[i] = 2 * i + 1;
		B[i] = i - 1;
		C[i] = A[i] + B[i];
	}

	ASSERT_TRUE(C == A + B);

	A += B;
	ASSERT_TRUE(C == A);
}

TEST(ArrayOps, Difference) {
	Array<int, 100> A;
	Array<int, 100> B;
	Array<int, 100> C;

	for (int i = 0; i < 100; ++i) {
		A[i] = 2 * i + 1;
		B[i] = i - 1;
		C[i] = A[i] - B[i];
	}

	ASSERT_TRUE(C == A - B);

	A -= B;
	ASSERT_TRUE(C == A);
}

TEST(ArrayOps, Product) {
	Array<int, 100> A;
	Array<int, 100> B;
	Array<int, 100> C;

	for (int i = 0; i < 100; ++i) {
		A[i] = 2 * i + 1;
		B[i] = i - 1;
		C[i] = A[i] * B[i];
	}

	ASSERT_TRUE(C == A * B);

	A *= B;
	ASSERT_TRUE(C == A);
}

TEST(ArrayOps, Quotient) {
	Array<int, 100> A;
	Array<int, 100> B;
	Array<int, 100> C;

	for (int i = 0; i < 100; ++i) {
		A[i] = 2 * i + 1;
		B[i] = i * 3 + 1;
		C[i] = A[i] / B[i];
	}

	ASSERT_TRUE(C == A / B);

	A /= B;
	ASSERT_TRUE(C == A);
}

TEST(ArrayOps, DivideByZero) {
	Array<int, 100> A;
	Array<int, 100> B;

	for (int i = 0; i < 100; ++i) {
		A[i] = 2 * i + 1;
		B[i] = 0;
	}

	ASSERT_THROW(A / B, MathLib::Exceptions::DivideByZero);
}

TEST(ArrayOps, BigArithmetic) {
	const unsigned int N = 10000000;
	Array<int, N>* A = new Array<int, N>();
	Array<int, N>* B = new Array<int, N>();
	Array<int, N>* C = new Array<int, N>();

	for (int i = 0; i < N; ++i) {
		(*A)[i] = 2 * i + 1;
		(*B)[i] = i - 1;
		(*C)[i] = (*A)[i] + (*B)[i];
	}

	ASSERT_TRUE(*C == *A + *B);

	delete A;
	delete B;
	delete C;
}

TEST(ArrayOps, MapFunction) {
	const unsigned int N = 1000;
	Array<int, N>* A = new Array<int, N>();
	Array<int, N>* B = new Array<int, N>();

	auto lambda = [](int x) {return x * x; };
	for (int i = 0; i < N; ++i) {
		(*A)[i] = i;
		(*B)[i] = i * i;
	}
	
	auto C = A->Map(lambda);

	ASSERT_TRUE(C == *B);
}

TEST(ArrayOps, StringOpPass) {
	Array<std::string, 100> A;
	Array<std::string, 100> B;
	Array<std::string, 100> C;

	for (int i = 0; i < 100; ++i) {
		A[i] = "a";
		B[i] = "b";
		C[i] = A[i] + B[i];
	}

	ASSERT_TRUE(C == A + B);
}

TEST(ArrayShape, Flatten) {
	MultiArray<int, 5> V = {
		0, 1, 2, 3, 4
	};

	auto W = V.Flatten();
	ASSERT_TRUE(W == V);

	MultiArray<int, 5, 4> M = {
		{0, 1, 2, 3},
		{4, 5, 6, 7},
		{8, 9, 0, 1},
		{2, 3, 4, 5},
		{6, 7, 8, 9}
	};

	auto N = M.Flatten();
	std::cout << N.ToString();
}