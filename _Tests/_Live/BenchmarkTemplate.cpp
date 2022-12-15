//#include <iostream>
//#include <chrono>
//
//// Add your imports here
//
//#define LOOPS 1
//
//// Add scopes here for simplifications
//
//int your_function_name_here()
//{
//	// Insert declarations here
//
//	double count = 0;
//	for (unsigned i = 0; i < LOOPS; ++i) {
//		auto start = std::chrono::high_resolution_clock::now();
//
//		// Insert your code here
//
//		auto end = std::chrono::high_resolution_clock::now();
//
//		count += (end - start).count() / 1e9;
//	}
//
//	std::cout << count / LOOPS << "s";
//
//	_CrtDumpMemoryLeaks();
//	return 0;
//}