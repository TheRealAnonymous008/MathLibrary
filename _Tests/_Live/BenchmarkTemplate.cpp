#include <iostream>
#include <chrono>

// Add your imports here

#define LOOPS 1

// Add scopes here for simplifications

int your_function_name_here()
{
	// Insert declarations here

	double count = 0;
	double min = FLT_MAX;
	double max = FLT_MIN;

	for (unsigned i = 0; i < LOOPS; ++i) {
		auto start = std::chrono::high_resolution_clock::now();

		// Insert your code here

		auto end = std::chrono::high_resolution_clock::now();

		auto time = (end - start).count() / 1e9;
		min = std::min(time, min);
		max = std::max(time, max);

		count += time;
 
	}

	std::cout << "Loops: " << LOOPS << "\n";
	std::cout << "Mean: " << count / LOOPS << "s\n";
	std::cout << "Min: " << min << "s\n";
	std::cout << "Max: " << max << "s\n";

	_CrtDumpMemoryLeaks();
	return 0;
}