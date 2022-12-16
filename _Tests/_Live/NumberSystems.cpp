//#include "headers/Benchmarker.h"
//#include "generators/NumberSystems.h"
//#include "../../NumberSystems/Core.h"
//
//using namespace Benchmarking;
//using namespace MathLib::NumberSystems;
//
//void Addition(Benchmark& b) {
//
//	auto x = Generator::NaturalNumber<1000>();
//	auto y = Generator::NaturalNumber<1000>();
//
//	b.Start();
//	x + y;
//	b.Stop();
//}
//
//void Subtraction(Benchmark& b) {
//
//	auto x = Generator::NaturalNumber<200>();
//	auto y = Generator::NaturalNumber<200>();
//
//	b.Start();
//	x - y;
//	b.Stop();
//}
//
//void Multiplication(Benchmark& b) {
//
//	auto x = Generator::NaturalNumber<1000>();
//	auto y = Generator::NaturalNumber<1000>();
//
//	b.Start();
//	x* y;
//	b.Stop();
//}
//
//void Division(Benchmark& b) {
//
//	auto x = Generator::NaturalNumber<1000>();
//	auto y = Generator::NaturalNumber<100>();
//
//	b.Start();
//	x / y;
//	b.Stop();
//}
//
//void Modulo(Benchmark& b) {
//
//	auto x = Generator::NaturalNumber<1000>();
//	auto y = Generator::NaturalNumber<100>();
//
//	b.Start();
//	x% y;
//	b.Stop();
//}
//
//void NOT(Benchmark& b) {
//
//	auto x = Generator::NaturalNumber<1000>();
//
//	b.Start();
//	~x;
//	b.Stop();
//}
//
//void AND(Benchmark& b) {
//
//	auto x = Generator::NaturalNumber<1000>();
//	auto y = Generator::NaturalNumber<1000>();
//
//	b.Start();
//	x& y;
//	b.Stop();
//}
//
//void OR(Benchmark& b) {
//
//	auto x = Generator::NaturalNumber<1000>();
//	auto y = Generator::NaturalNumber<1000>();
//
//	b.Start();
//	x | y;
//	b.Stop();
//}
//
//void XOR(Benchmark& b) {
//
//	auto x = Generator::NaturalNumber<1000>();
//	auto y = Generator::NaturalNumber<1000>();
//
//	b.Start();
//	x^ y;
//	b.Stop();
//}
//
//void LeftShift(Benchmark& b) {
//
//	auto x = Generator::NaturalNumber<1000>();
//	auto y = Generator::NaturalNumber<5>();
//
//	b.Start();
//	x << y;
//	b.Stop();
//}
//
//void RightShift(Benchmark& b) {
//
//	auto x = Generator::NaturalNumber<1000>();
//	auto y = Generator::NaturalNumber<5>();
//
//	b.Start();
//	x >> y;
//	b.Stop();
//}
//
//void EQ(Benchmark& b) {
//
//	auto x = Generator::NaturalNumber<1000>();
//	auto y = Generator::NaturalNumber<1000>();
//
//	b.Start();
//	x == y;
//	b.Stop();
//}
//
//void NEQ(Benchmark& b) {
//
//	auto x = Generator::NaturalNumber<1000>();
//	auto y = Generator::NaturalNumber<1000>();
//
//	b.Start();
//	x != y;
//	b.Stop();
//}
//
//void GR(Benchmark& b) {
//
//	auto x = Generator::NaturalNumber<1000>();
//	auto y = Generator::NaturalNumber<1000>();
//
//	b.Start();
//	x > y;
//	b.Stop();
//}
//
//void LE(Benchmark& b) {
//
//	auto x = Generator::NaturalNumber<1000>();
//	auto y = Generator::NaturalNumber<1000>();
//
//	b.Start();
//	x < y;
//	b.Stop();
//}
//
//void GREQ(Benchmark& b) {
//
//	auto x = Generator::NaturalNumber<1000>();
//	auto y = Generator::NaturalNumber<1000>();
//
//	b.Start();
//	x >= y;
//	b.Stop();
//}
//
//void LEQ(Benchmark& b) {
//
//	auto x = Generator::NaturalNumber<1000>();
//	auto y = Generator::NaturalNumber<1000>();
//
//	b.Start();
//	x <= y;
//	b.Stop();
//}
//int main() {
//
//	Benchmark("Addition", Addition).Run(1000).ShowReport();
//	Benchmark("Subtraction", Subtraction).Run(1000).ShowReport();
//	Benchmark("Multiplication", Multiplication).Run(1000).ShowReport();
//	Benchmark("Division", Division).Run(1000).ShowReport();
//	Benchmark("Modulo", Modulo).Run(1000).ShowReport();
//
//	Benchmark("NOT", NOT).Run(1000).ShowReport();
//	Benchmark("AND", AND).Run(1000).ShowReport();
//	Benchmark("OR", OR).Run(1000).ShowReport();
//	Benchmark("XOR", XOR).Run(1000).ShowReport();
//
//	Benchmark("LEFT SHIFT", LeftShift).Run(1000).ShowReport();
//	Benchmark("RIGHT SHIFT", RightShift).Run(1000).ShowReport();
//
//	Benchmark("==", EQ).Run(1000).ShowReport();
//	Benchmark("!=", NEQ).Run(1000).ShowReport();
//	Benchmark(">", GR).Run(1000).ShowReport();
//	Benchmark("<", LE).Run(1000).ShowReport();
//	Benchmark(">=", GREQ).Run(1000).ShowReport();
//	Benchmark("<=", LEQ).Run(1000).ShowReport();
//
//	return 0;
//}