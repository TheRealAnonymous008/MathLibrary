#pragma once

#include<vector>

inline void GenerateReport(std::vector<double> samples) {
	std::cout << "Benchmark report\n";
	double sum = 0;
	auto count = samples.size();

	for (auto s : samples) {
		sum += s;
	}

	double average = sum / count;
	auto min = std::ranges::min_element(samples);
	auto max = std::ranges::max_element(samples);

	sum = 0;
	for (auto s : samples) {
		sum += (s - average) * (s - average);
	}

	double stddev = std::sqrt(sum / count);

	std::cout << "Samples:\t" << count << "\n";
	std::cout << "Average:\t" << average << "\n";
	std::cout << "Min:\t\t" << *min << "\n";
	std::cout << "Max:\t\t" << *max << "\n";
	std::cout << "Stddev:\t\t" << stddev << "\n";
}