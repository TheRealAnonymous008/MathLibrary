#include <fstream>

#include "headers/Benchmarker.h"
#include "generators/NumberSystems.h"
#include "../../NumberSystems/Core.h"

using namespace Benchmarking;
using namespace MathLib::NumberSystems;

void Addition(Benchmark& b) {

	auto x = Generator::NaturalNumber<1000>();
	auto y = Generator::NaturalNumber<1000>();

	b.Start();
	x + y;
	b.Stop();
}

void Subtraction(Benchmark& b) {

	auto x = Generator::NaturalNumber<200>();
	auto y = Generator::NaturalNumber<200>();

	b.Start();
	x - y;
	b.Stop();
}

void Multiplication(Benchmark& b) {

	auto x = Generator::NaturalNumber<1000>();
	auto y = Generator::NaturalNumber<1000>();

	b.Start();
	x* y;
	b.Stop();
}

void Division(Benchmark& b) {

	auto x = Generator::NaturalNumber<1000>();
	auto y = Generator::NaturalNumber<100>();

	b.Start();
	x / y;
	b.Stop();
}

void Modulo(Benchmark& b) {

	auto x = Generator::NaturalNumber<1000>();
	auto y = Generator::NaturalNumber<100>();

	b.Start();
	x% y;
	b.Stop();
}

void NOT(Benchmark& b) {

	auto x = Generator::NaturalNumber<1000>();

	b.Start();
	~x;
	b.Stop();
}

void AND(Benchmark& b) {

	auto x = Generator::NaturalNumber<1000>();
	auto y = Generator::NaturalNumber<1000>();

	b.Start();
	x& y;
	b.Stop();
}

void OR(Benchmark& b) {

	auto x = Generator::NaturalNumber<1000>();
	auto y = Generator::NaturalNumber<1000>();

	b.Start();
	x | y;
	b.Stop();
}

void XOR(Benchmark& b) {

	auto x = Generator::NaturalNumber<1000>();
	auto y = Generator::NaturalNumber<1000>();

	b.Start();
	x^ y;
	b.Stop();
}

void LeftShift(Benchmark& b) {

	auto x = Generator::NaturalNumber<1000>();
	auto y = Generator::NaturalNumber<5>();

	b.Start();
	x << y;
	b.Stop();
}

void RightShift(Benchmark& b) {

	auto x = Generator::NaturalNumber<1000>();
	auto y = Generator::NaturalNumber<5>();

	b.Start();
	x >> y;
	b.Stop();
}

void EQ(Benchmark& b) {

	auto x = Generator::NaturalNumber<1000>();
	auto y = Generator::NaturalNumber<1000>();

	b.Start();
	x == y;
	b.Stop();
}

void NEQ(Benchmark& b) {

	auto x = Generator::NaturalNumber<1000>();
	auto y = Generator::NaturalNumber<1000>();

	b.Start();
	x != y;
	b.Stop();
}

void GR(Benchmark& b) {

	auto x = Generator::NaturalNumber<1000>();
	auto y = Generator::NaturalNumber<1000>();

	b.Start();
	x > y;
	b.Stop();
}

void LE(Benchmark& b) {

	auto x = Generator::NaturalNumber<1000>();
	auto y = Generator::NaturalNumber<1000>();

	b.Start();
	x < y;
	b.Stop();
}

void GREQ(Benchmark& b) {

	auto x = Generator::NaturalNumber<1000>();
	auto y = Generator::NaturalNumber<1000>();

	b.Start();
	x >= y;
	b.Stop();
}

void LEQ(Benchmark& b) {

	auto x = Generator::NaturalNumber<1000>();
	auto y = Generator::NaturalNumber<1000>();

	b.Start();
	x <= y;
	b.Stop();
}
int main() {

	Benchmark benchmark = Benchmark("NumberSystems");

	benchmark
		.Run("Addition", Addition, 1000)
		.Run("Subtraction", Subtraction, 1000)
		.Run("Multiplication", Multiplication, 1000)
		.Run("Division", Division, 1000)
		.Run("Modulo", Modulo, 1000)
		.AddEmptyRow()
		.Run("NOT", NOT, 1000)
		.Run("AND", AND, 1000)
		.Run("OR", OR, 1000)
		.Run("XOR", XOR, 1000)
		.Run("LEFT SHIFT", LeftShift, 1000)
		.Run("RIGHT SHIFT", RightShift, 1000)
		.AddEmptyRow()
		.Run("==", EQ, 1000)
		.Run("!=", NEQ, 1000)
		.Run(">", GR, 1000)
		.Run("<", LE, 1000)
		.Run(">=", GREQ, 1000)
		.Run("<=", LEQ, 1000);


	std::ofstream report;
	report.open(benchmark.Name() + ".md");
	report << benchmark.Out();
	report.close();

	return 0;
}