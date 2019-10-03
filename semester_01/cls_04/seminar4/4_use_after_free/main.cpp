#include <cstdio>

static void processArray(int* arr, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        arr[i] = i;
    }

    delete[] arr;
}

int main() {

    int* array = new int[100]();

    processArray(array, 100);

    array[0] = 32; // Error: use after free

    delete[] array; // Error: double free

    return 0;
}

// clang++ -std=c++17 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -O0 main.cpp && ./a.out