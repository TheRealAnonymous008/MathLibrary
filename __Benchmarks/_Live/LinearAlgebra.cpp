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
			.Run("Matrix Scalar Division", MatrixScalarQuotient, 1000);

		std::ofstream report;
		report.open(benchmark.Name() + ".md");
		report << benchmark.Out();
		report.close();
	
		return 0;
}