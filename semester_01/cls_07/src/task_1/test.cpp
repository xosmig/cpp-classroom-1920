#include <iostream>
#include <cassert>
#include <string>
#include <cstring>
#include "../lazy_string.hpp"

static void test_lazy_string_find() {
    {
        cls_08::lazy_string empty;

        assert(find(empty, "") == 0);
        assert(find(empty, "", 0) == 0);
        assert(find(empty, "", 1) == -1);

        assert(find(empty, "smth") == -1);
        assert(find(empty, "smth", 0) == -1);
        assert(find(empty, "smth", 1) == -1);
    }

    {
        cls_08::lazy_string hello {"Hello world!"};

        assert(find(hello, "H") == 0);
        assert(find(hello, "e") == 1);
        assert(find(hello, "!") == 11);

        assert(find(hello, "H", 1) == -1);

        assert(find(hello, "Hello") == 0);
        assert(find(hello, "world") == 6);
        assert(find(hello, "world", 6) == 6);
    }

    {
        cls_08::lazy_string str = "one@two@three@four";

        assert(find(str, "@") == 3);
        assert(find(str, "@", 4) == 7);
        assert(find(str, "@", 8) == 13);
        assert(find(str, "@", 14) == -1);

        assert(find(str, "@", 1024) == -1);
    }
}

int main() {
    test_lazy_string_find();
}