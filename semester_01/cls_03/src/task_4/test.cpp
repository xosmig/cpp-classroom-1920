#include <cassert>
#include <iostream>
#include "matrices.hpp"

void test_matrix() {
    auto matrix = create_matrix(2, 2);

    assert(matrix[0][0] == 0);
    assert(matrix[0][1] == 0);
    assert(matrix[1][0] == 0);
    assert(matrix[1][1] == 0);

    matrix[0][1] = 10;
    matrix[1][0] = 20;

    assert(matrix[0][0] == 0);
    assert(matrix[0][1] == 10);
    assert(matrix[1][0] == 20);
    assert(matrix[1][1] == 0);

    release_matrix(matrix);
}

int main() {
    test_matrix();

    std::cout << "Task 4 tests completed successfully!" << std::endl;

    return 0;
}