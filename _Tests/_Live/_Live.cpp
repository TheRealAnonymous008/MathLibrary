#include <iostream>
#include <chrono>

#include "../../NumberSystems/Core.h"

#define LOOPS 100

// Add scopes here for simplifications
using namespace MathLib::NumberSystems;

int main()
{
	// Insert declarations here
	Natural x = Natural("267,895,894,304,364,752,678,868,955,431,824,907,367,753,146,322,020,621,335,624,329,595,212,336,512,781,781,585,428,916,823,953,974,814,585,680,226,678,326,375,639,556,132,623,499,217,174,608,843,391,469,389,219,335,124,993,828,874,277,769,329,364,543,105,366,842");
	Natural y = Natural("293472749235728428357126940735827434810239242572935092398472871028038485776249124983758612483248394");

	double count = 0;
	for (unsigned i = 0; i < LOOPS; ++i) {
		auto start = std::chrono::high_resolution_clock::now();

		// Insert your code here
		x % y;

		auto end = std::chrono::high_resolution_clock::now();

		count += (end - start).count() / 1e9;
	}

	std::cout << count / LOOPS <<"s";

	_CrtDumpMemoryLeaks();
	return 0;
}