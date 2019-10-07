#include "for_each.hpp"

#include <cassert>
#include <vector>
#include <iostream>

static int storage = 0;

static void test_for_each() {
    storage = 0;
    {
        for_each({}, [](int i) { storage += i; });
        assert(storage == 0);
    }

    storage = 0;
    {
        for_each({1, 2, 3}, [](int i) { storage += i; });
        assert(storage == 6);
    }

    storage = 0;
    {
        std::vector<int> vec {0, 1, 2, 3, 4};
        for_each(vec, [](int i) {
            assert(storage == i);
            storage += 1;
        });
    }
}

int main() {
    test_for_each();

    std::cout << "Task 1 tests completed successfully!" << std::endl;
}