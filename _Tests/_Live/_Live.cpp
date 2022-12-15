#include <iostream>
#include <chrono>

#include "Statistics.h"

#include "../../NumberSystems/Core.h"

#define LOOPS 10000

// Add scopes here for simplifications
using namespace MathLib::NumberSystems;

int main()
{
	// Insert declarations here
	Natural x = Natural("267895894304364752678868955431824907367753146322020621335624329595212336512781781585428916823953974814585680226678326375639556132623499217174608843391469389219335124993828874277769329364543105366842");
	Natural y = Natural("123891283128439248174320582841273598395882475048372462483812489102301243959359102010230503692851923811752304012402350239187328382337777123819021492857375287351249182498527417291129938375637642654341");
	Natural z = Natural("123891283128439248174320582841273598395882475048372462483812489102301243959359102010230503692851923811752304012402350239187328382");

	Natural l = Natural(45);
	Natural s = Natural(1000000);

	std::vector<double> samples;

	for (unsigned i = 0; i < LOOPS; ++i) {
		auto start = std::chrono::high_resolution_clock::now();

		// Insert your code here
		x * y;

		auto end = std::chrono::high_resolution_clock::now();

		auto time = (end - start).count() / 1e9;
		samples.push_back(time);
	}

	GenerateReport(samples);

	_CrtDumpMemoryLeaks();
	return 0;
}