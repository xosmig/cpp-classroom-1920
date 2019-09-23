#include <iostream>
#include <cassert>

void test_sum() {
    assert(sum({}, 0) == 0 && "Sum of empty array should be equal zero!");

    {
        int array[]{1, 2, 3, 4, 5};

        assert(sum(array, 0) == 0 && "Sum of empty array should be equal zero!");

        assert(sum(array + 0, 1) == 1);
        assert(sum(array + 1, 1) == 2);
        assert(sum(array + 2, 1) == 3);
        assert(sum(array + 3, 1) == 4);
        assert(sum(array + 4, 1) == 5);

        assert(sum(array, 5) == 15);
    }

    {
        int const array[10]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        assert(sum(array, sizeof(array) / sizeof(int)) == 55);
    }
}

void test_mins_suffix() {
    {
        int array[]{2, 2, 1, 3};

        auto result = mins_suffix(array, 4);
        assert(result[0] == array);
        assert(result[1] == array);
        assert(result[2] == array + 2);
        assert(result[3] == array + 2);

        delete[] result;
    }
}

void test_min() {
    {
        int const array[]{1, 3, 5, 16, -3, 4, 2, -3};

        assert(*min(array, 0, 8) == -3 && min(array, 0, 8) == array + 4);
        assert(*min(array, 0, 3) == 1 && min(array, 0, 3) == array);
        assert(*min(array + 1, 0, 3) == 3 && min(array + 1, 0, 3) == array + 1);

        assert(min(array, 3, 2) == nullptr);
    }

}

int main() {
    test_sum();
    test_mins_suffix();
    test_min();

    std::cout << "Task 1 tests completed successfully!" << std::endl;

    return 0;
}
