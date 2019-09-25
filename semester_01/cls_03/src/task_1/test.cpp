#include <iostream>
#include <cassert>

static void test_sum() {
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

static void test_count_numbers() {
    assert(count_numbers({}, 0) == 0);

    {
        int const arr[] {1, 2, 3, 4, 5, 4, 3, 2, 1};

        assert(count_numbers(arr, 0) == 0);
        assert(count_numbers(arr, 1) == 1);
        assert(count_numbers(arr, 3) == 3);

        assert(count_numbers(arr, sizeof(arr) / sizeof(int)) == 5);
    }
}

static void test_sort() {
    {
        int const arr[] {1, 2, 3, 4, 5};
        auto result = sort(arr, sizeof(arr) / sizeof(int));

        for (size_t i = 0; i < 5; ++i) {
            assert(result[i] == arr + i);
        }

        delete[] result;
    }

    {
        int const arr[] {5, 4, 3, 2, 1};
        auto result = sort(arr, sizeof(arr) / sizeof(int));

        for (size_t i = 0; i < 5; ++i) {
            assert(result[5 - i - 1] == arr + i);
        }

        delete[] result;
    }
}

int main() {
    test_sum();
    test_count_numbers();
    test_sort();

    std::cout << "Task 1 tests completed successfully!" << std::endl;

    return 0;
}
