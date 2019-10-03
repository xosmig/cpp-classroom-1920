#include <iostream>

void overflowAccess(int* arr, size_t n) {
	arr[n] = 10;
    std::cout << arr[0];
}

int main() {
    int array[10]{0};
    overflowAccess(array, 10);

    return 0;
}

// clang++ -std=c++17 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -O3 main.cpp && ./a.out
// UNDEFINED_BEHAVIOR