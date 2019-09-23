#include <cassert>
#include <iostream>
#include "ladder_combinations.hpp"

void test_ladder_combinations() {
    assert(ladder_combinations(0) == 1);

    assert(ladder_combinations(1) == 1);
    assert(ladder_combinations(2) == 2);
    assert(ladder_combinations(3) == 3);
    assert(ladder_combinations(4) == 5);

    assert(ladder_combinations(20) == 10946);
}

int main() {
    test_ladder_combinations();

    std::cout << "Task 2 tests completed successfully!" << std::endl;

    return 0;
}