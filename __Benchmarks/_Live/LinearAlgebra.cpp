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

void VectorNorm(Benchmark& b) {
	auto v = Generator::Vector<1000>();

	b.Start();
	Norm(v);
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
			.Run("Vector Norm", VectorNorm, 1000);
		std::ofstream report;
		report.open(benchmark.Name() + ".md");
		report << benchmark.Out();
		report.close();
	
		return 0;
}