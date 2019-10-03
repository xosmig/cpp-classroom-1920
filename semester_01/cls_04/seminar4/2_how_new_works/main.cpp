#include <iostream>

using namespace std;

void* operator new[](size_t size)
{
    cout << "OPERATOR NEW[] CALLED" << endl;
    return malloc(size);
}

void operator delete[](void* p) noexcept
{
    cout << "OPERATOR DELETE[] CALLED" << endl;
    free(p);
}

int main() {

    // array
    int* arr = new int[10]{0, 1};
    /* explanation:
        Roughly speaking, expression `new int[10]{1, 0}` works as follows:

            void* ptr = ::operator new[](10 * sizeof(int));   // calling of operator new
            int* arr = static_cast<int*>(ptr);              // casting
            std::fill_n(arr, 10, 0);                        // initializing
            arr[0] = 0;
            arr[1] = 1;
    */
    delete[] arr;

    return 0;
}

/*
References:
* https://habr.com/ru/post/185662/

* https://en.cppreference.com/w/cpp/language/new
* https://en.cppreference.com/w/cpp/memory/new/operator_new
*/