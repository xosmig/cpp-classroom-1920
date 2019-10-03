#include <iostream>

#include "speaker.hpp"

#include "say_hello.cpp" // Bad way: don't include *.cpp

// `clang++ --std=c++17 *.cpp` raises linker error: duplicate symbol 'sayHello()'

int main() {

    for (size_t i = 0; i < 5; ++i) {
        sayRandomWords();
    }

    sayHello();

    return 0;
}