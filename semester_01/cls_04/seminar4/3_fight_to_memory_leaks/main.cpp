#include <iostream>

// how to get memory leaks see here: https://en.cppreference.com/w/cpp/language/new

static void memleak() {
    int* p = new int[10];
}

static void g(int* p) {
    std::cout << p[0];
    throw std::runtime_error("ups");
}

static void memleak_with_throw() {
    int* p = new int[10]{};

    g(p);

    delete[] p;
}

int main() {

    // case 1:
    int* p = new int[10]{1,2,3};
    p = nullptr;

    // case 2:
    {
        int* ptr = new int[10];
    }

    // case 3:
    memleak();

    // case 4:
    try {
        memleak_with_throw();
    } catch (...) {
        // pass
    }

    return 0;
}

/*
Ways to detect memory leaks:

1. Sanitizers
Go here to check: http://coliru.stacked-crooked.com
    clang++ -std=c++17 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -O0 main.cpp && ./a.out
    or
    clang++ -std=c++17 -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -O0 main.cpp && ASAN_OPTIONS=detect_leaks=1 ./a.out

2. Valgrind
    g++ -std=c++17 -O0 memleak.cpp
    valgrind --leak-check=yes ./a.out
*/
