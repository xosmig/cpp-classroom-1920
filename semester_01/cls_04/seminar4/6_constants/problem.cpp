// Find problem here
#include <iostream>

#define PI 3.1415;

int main() {

	// Compile code to see warning: expression result unused [-Wunused-value]
	auto doubledPI = PI + PI;
	std::cout << doubledPI;

	// Use `clang++ -E -std=c++17 problem.cpp` to see preprocessed code.
	// Pay attention to line 9.

	return 0;
}