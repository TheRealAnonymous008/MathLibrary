#include "headers/Benchmarker.h"
#include "generators/NumberSystems.h"
#include "../../NumberSystems/Core.h"

using namespace Benchmarking;
using namespace MathLib::NumberSystems;

void Addition(Benchmark& b) {

	auto x = Generator::NaturalNumber<100>();
	auto y = Generator::NaturalNumber<100>();

	b.Start();
	x + y;
	b.Stop();
}

int main() {
	
	Benchmark("Addition", Addition).Run(10000).ShowReport();

	return 0;
}