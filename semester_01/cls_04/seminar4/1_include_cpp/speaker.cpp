#include "speaker.hpp"

#include "say_hello.cpp" // Bad way: don't include *.cpp

#include <iostream>

void sayRandomWords() {
    int needToSayHello = rand() % 2;

    if (needToSayHello) {
        sayHello();
    } else {
        std::cout << "Sorry, nothing to say(" << std::endl;
    }
}