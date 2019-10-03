#include <iostream>

int main() {
    int* array = new int[10]();
    array[10] = 100; // Error: heap-buffer-overflow

    std::cout << array[0];

    return 0;
}

// clang++ -std=c++17 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -O0 main.cpp && ./a.out