//#include "headers/Benchmarker.h"
//
//using namespace Benchmarking;
//
//void Sample(Benchmark& b) {
//	b.Start();
//	auto val = 0;
//	for (int i = 0; i < 10000; ++i) {
//		++val;
//	}
//	b.Stop();
//}
//
//int Template() {
//
//	Benchmark b = Benchmark(Sample);
//	b.Run();
//	b.ShowReport();
//	return 0;
//}