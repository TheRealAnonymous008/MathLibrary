//#include <iostream>
//#include <chrono>
//
//#include "Statistics.h"
//
//#include "../../NumberSystems/Core.h"
//
//#define LOOPS 1000000
//
//// Add scopes here for simplifications
//using namespace MathLib::NumberSystems;
//
//int main()
//{
//	// Insert declarations here
//
//	// End of declarations
//
//	std::vector<double> samples;
//
//	for (unsigned i = 0; i < LOOPS; ++i) {
//		auto start = std::chrono::high_resolution_clock::now();
//
//		// Insert your code here
//
//		auto end = std::chrono::high_resolution_clock::now();
//
//		auto time = (end - start).count() / 1e9;
//		samples.push_back(time);
//	}
// 
//	GenerateReport(samples);
//
//	_CrtDumpMemoryLeaks();
//	return 0;
//}