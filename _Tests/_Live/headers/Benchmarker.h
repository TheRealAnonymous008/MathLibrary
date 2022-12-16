#pragma once

#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace Benchmarking {
	class BenchmarkReport {
	private:
		double mean;
		double stddev;
		unsigned count;
		std::string name; 

		double CalculateMean(std::vector<double> samples) const {
			double sum = 0;
			for (auto d : samples) {
				sum += d;
			}
			return sum / samples.size();
		}

		double CalculateStddev(std::vector<double> samples, double u) const {
			double sum = 0;
			for (auto d : samples) {
				sum += (d - u) * (d - u);
			}
			return std::sqrt(sum / samples.size());
		}

	public:
		BenchmarkReport(std::string name, std::vector<double> samples) {
			this->name = name;
			this->count = samples.size();
			this->mean = CalculateMean(samples);
			this->stddev = CalculateStddev(samples, mean);
		}

		std::string operator() () {
			std::stringstream ss;
			ss << "| " << this->name << " | " << count << " | " << mean << " | " << stddev << " |";
			return ss.str();
		}
	};

	class Benchmark {
	private:
		std::vector<double> samples;
		std::chrono::high_resolution_clock::time_point time_start;

		std::string output = "";

		void UpdateReport(std::string name) {
			BenchmarkReport report = BenchmarkReport(name, samples);
			output += report() + "\n";
		}

	public:

		Benchmark() {
			AddHeaders();
			AddEmptyRow();
		}

		Benchmark& Run(std::string name, std::function<void(Benchmark&)> func, unsigned loops = 1) {

			std::cout << "Running tests for " << name << "...\n";
			unsigned i = 0;
			this->samples.clear();

			#pragma omp parallel
			while(i < loops) {
				try {
					func(*this);
					++i;
				}
				catch (std::exception) {

				}
			}
			UpdateReport(name);

			return *this;
		}

		void Start() {
			this->time_start = std::chrono::high_resolution_clock::now();
		}

		Benchmark& AddHeaders() {
			output += "Operation | Samples | Mean (s) | Stddev (s) |\n";
			return *this;

		}

		Benchmark& AddEmptyRow() {
			output += " ---| --- | --- | --- |\n";
			return *this;
		}
 
		void Stop() {
			auto time_end = std::chrono::high_resolution_clock::now();
			double time = (time_end - time_start).count() / 1e9;

			#pragma omp critical
			samples.push_back(time);
		}

		std::string Out() const {
			return output;
		}
	};
}