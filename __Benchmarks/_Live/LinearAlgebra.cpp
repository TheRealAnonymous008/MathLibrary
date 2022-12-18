#include <fstream>

#include "headers/Benchmarker.h"
#include "generators/LinearAlgebra.h"
#include "../../LinearAlgebra/Core.h"

using namespace Benchmarking;
using namespace MathLib::LinearAlgebra;

void VectorAddition(Benchmark& b) {
	auto v = Generator::Vector<1000>();
	auto w = Generator::Vector<1000>();

	b.Start();
	
	(v + w).Evaluate();

	b.Stop();
}

void VectorSubtraction(Benchmark& b) {
	auto v = Generator::Vector<1000>();
	auto w = Generator::Vector<1000>();

	b.Start();

	(v - w).Evaluate();

	b.Stop();
}

void VectorScalarMultiplication(Benchmark& b) {
	auto v = Generator::Vector<1000>();
	auto c = Generator::Scalar();

	b.Start();
	(v * c).Evaluate();
	b.Stop();
}

void VectorScalarDivision(Benchmark& b) {
	auto v = Generator::Vector<1000>();
	auto c = Generator::Scalar();

	b.Start();
	(v / c).Evaluate();
	b.Stop();
}

void VectorNegation(Benchmark& b) {
	auto v = Generator::Vector<1000>();

	b.Start();
	(-v).Evaluate();
	b.Stop();
}

void VectorDotProduct(Benchmark& b) {
	auto v = Generator::Vector<1000>();
	auto w = Generator::Vector<1000>();

	b.Start();
	Dot(v, w);
	b.Stop();
}

void VectorSquareNorm(Benchmark& b) {
	auto v = Generator::Vector<1000>();

	b.Start();
	SquareNorm(v);
	b.Stop();
}
void VectorNorm(Benchmark& b) {
	auto v = Generator::Vector<1000>();

	b.Start();
	Norm(v);
	b.Stop();
}

void VectorNormalize(Benchmark& b) {
	auto v = Generator::Vector<1000>();

	b.Start();
	Normalize(v);
	b.Stop();
}

void VectorIsNormal(Benchmark& b) {
	auto v = Generator::Vector<1000>();

	b.Start();
	IsNormal(v);
	b.Stop();
}

void VectorIsOrthogonal(Benchmark& b) {
	auto v = Generator::Vector<1000>();
	auto w = Generator::Vector<1000>();

	b.Start();
	IsOrthogonal(v, w);
	b.Stop();
}

void VectorIsOrthonormal(Benchmark& b) {
	auto v = Generator::Vector<1000>();
	auto w = Generator::Vector<1000>();

	b.Start();
	IsOrthonormal(v, w);
	b.Stop();
}

void MatrixAddition(Benchmark& b) {
	auto M = Generator::Matrix<1000, 1000>();
	auto N = Generator::Matrix<1000, 1000>();

	b.Start();
	(M + N).Evaluate();
	b.Stop();
}

void MatrixSubtraction(Benchmark& b) {
	auto M = Generator::Matrix<1000, 1000>();
	auto N = Generator::Matrix<1000, 1000>();

	b.Start();
	(M - N).Evaluate();
	b.Stop();
}

void MatrixNegation(Benchmark& b) {
	auto M = Generator::Matrix<1000, 1000>();

	b.Start();
	(-M).Evaluate();
	b.Stop();
}

void MatrixScalarProduct(Benchmark& b) {
	auto M = Generator::Matrix<1000, 1000>();
	auto c = Generator::Scalar();

	b.Start();
	(M * c).Evaluate();
	b.Stop();
}

void MatrixScalarQuotient(Benchmark& b) {
	auto M = Generator::Matrix<1000, 1000>();
	auto c = Generator::Scalar();

	b.Start();
	(M / c).Evaluate();
	b.Stop();
}

void MatrixVectorProduct(Benchmark& b) {
	auto M = Generator::Matrix<1000, 1000>();
	auto v = Generator::Vector<1000>();

	b.Start();
	(M * v).Evaluate();
	b.Stop();
}

void MatrixMultiplication(Benchmark& b) {
	auto M = Generator::Matrix<1024, 1024>();
	auto N = Generator::Matrix<1024, 1024>();

	b.Start();
	(M * N).Evaluate();
	b.Stop();
}

void MatrixTranspose(Benchmark& b) {
	auto M = Generator::Matrix<1000, 1000>();

	b.Start();
	Transpose(M).Evaluate();
	b.Stop();
}

void MatrixPlaceBlock(Benchmark& b) {
	auto M = Generator::Matrix<1000, 1000>();
	auto B = Generator::Matrix<100, 100>();

	b.Start();
	PlaceBlock(M, B, 100, 100);
	b.Stop();
}

void MatrixSlice(Benchmark& b) {
	auto M = Generator::Matrix<1000, 1000>();

	b.Start();
	Slice<500, 500>(M, 100, 100);
	b.Stop();
}

void MatrixTrace(Benchmark& b) {
	auto M = Generator::Matrix<1000, 1000>();

	b.Start();
	Trace (M);
	b.Stop();
}

void MatrixColumnPermutation (Benchmark& b) {
	auto M = Generator::Matrix<1000, 1000>();
	auto P = PermutationMatrix<double, 1000>(Generator::Permutation<1000>());

	b.Start();
	P * M;
	b.Stop();
}

void MatrixRowPermutation(Benchmark& b) {
	auto M = Generator::Matrix<1000, 1000>();
	auto P = PermutationMatrix<double, 1000>(Generator::Permutation<1000>());

	b.Start();
	(P * M).Evaluate();
	b.Stop();
}

void UpperTriangularTest(Benchmark& b) {
	auto M = Generator::Matrix<1000, 1000>();

	b.Start();
	IsUpper(M);
	b.Stop();
}


void LowerTriangularTest(Benchmark& b) {
	auto M = Generator::Matrix<1000, 1000>();

	b.Start();
	IsLower(M);
	b.Stop();
}


void DiagonalTest(Benchmark& b) {
	auto M = Generator::Matrix<1000, 1000>();

	b.Start();
	IsDiagonal(M);
	b.Stop();
}

void SymmetricTest(Benchmark& b) {
	auto M = Generator::Matrix<1000, 1000>();

	b.Start();
	IsSymmetric(M);
	b.Stop();
}


void LUPartial(Benchmark& b) {
	auto M = Generator::Matrix<1000, 1000>();

	b.Start();
	PartialLU(M);
	b.Stop();
}

void LUFull(Benchmark& b) {
	auto M = Generator::Matrix<1000, 1000>();

	b.Start();
	FullLU(M);
	b.Stop();
}

void LUSolve(Benchmark& b) {
	auto M = Generator::Matrix<1000, 1000>();
	auto v = Generator::Vector<1000>();

	b.Start();
	SolveLinearSystem(M, v);
	b.Stop();
}

void LUMatrixInverse(Benchmark& b) {
	auto M = Generator::Matrix<1000, 1000>();

	b.Start();
	Inverse(M);
	b.Stop();
}

int main() {
		Benchmark benchmark = Benchmark("LinearAlgebra");
	
		std::cout << "\n";
		
		benchmark
			.Run("Vector Addition", VectorAddition, 1000)
			.Run("Vector Subtraction", VectorSubtraction, 1000)
			.Run("Vector Scalar Multiplication", VectorScalarMultiplication, 1000)
			.Run("Vector Scalar Division", VectorScalarDivision, 1000)
			.Run("Vector Negation", VectorNegation, 1000)
			.AddEmptyRow()
			.Run("Vector Dot Product", VectorDotProduct, 1000)
			.Run("Vector Square Norm", VectorSquareNorm, 1000)
			.Run("Vector Norm", VectorNorm, 1000)
			.Run("Vector Normalize", VectorNormalize, 1000)
			.Run("Vector IsNormal", VectorIsNormal, 1000)
			.Run("Vector IsOrthogonal", VectorIsOrthogonal, 1000)
			.Run("Vector IsOrthonormal", VectorIsOrthonormal, 1000)
			.AddEmptyRow()
			.Run("Matrix Addition", MatrixAddition, 1000)
			.Run("Matrix Subtraction", MatrixSubtraction, 1000)
			.Run("Matrix Negation", MatrixNegation, 1000)
			.Run("Matrix Scalar Multiplication", MatrixScalarProduct, 1000)
			.Run("Matrix Scalar Division", MatrixScalarQuotient, 1000)
			.Run("Matrix Vector Multiplication", MatrixVectorProduct, 1000)
			.Run("Matrix Multiplication", MatrixMultiplication, 100)
			.AddEmptyRow()
			.Run("Matrix Transpose", MatrixTranspose, 1000)
			.Run("Matrix PlaceBlock", MatrixPlaceBlock, 1000)
			.Run("Matrix Slice", MatrixSlice, 1000)
			.Run("Matrix Trace", MatrixTrace, 1000)
			.Run("Matrix Column Permutation", MatrixColumnPermutation, 1000)
			.Run("Matrix Row Permutation", MatrixRowPermutation, 1000)
			.AddEmptyRow()
			.Run("Upper Triangular Test", UpperTriangularTest, 1000)
			.Run("Lower Triangular Test", LowerTriangularTest, 1000)
			.Run("Diagonal Test", DiagonalTest, 1000)
			.Run("Symmetric Test", SymmetricTest, 1000)
			.AddEmptyRow()
			.Run("Partial LU Decomposition", LUPartial, 100)
			.Run("Full LU Decomposition", LUFull, 100)
			.Run("Solver", LUSolve, 100)
			.Run("Matrix Inverse", LUMatrixInverse, 100)
			;

		std::ofstream report;
		report.open(benchmark.Name() + ".md");
		report << benchmark.Out();
		report.close();
	
		return 0;
}