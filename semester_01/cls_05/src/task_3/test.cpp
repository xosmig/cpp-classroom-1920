#include "combine.hpp"

#include <iostream>
#include <cassert>
#include <vector>

static void test_combine() {
    auto mult = [](double a, double b) { return a * b; };
    auto plus = [](double a, double b) { return a + b; };

    {
        assert(combine({}, mult, plus) == 0);
        assert(combine({1}, mult, plus) == 1);
        assert(combine({2}, mult, plus) == 2);
    }

    {
        assert(combine({1, 2, 3}, mult, plus) == (1. * 2.) + 3.);
        assert(combine({1, 2, 3, 4}, mult, plus) == (1 * 2) + (3 * 4));

        assert(combine({1, 2, 3, 4}, plus, plus) == (1. + 2.) + (3. + 4.));
    }
}


int main() {
    test_combine();

    std::cout << "Task 3 tests completed successfully!" << std::endl;
}
