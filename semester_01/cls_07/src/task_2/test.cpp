#include "../lazy_string.hpp"

#include <cassert>
#include <cstring>
#include <string>
#include <sstream>

static std::string to_string(cls_07::lazy_string const& str) {
    std::stringstream ss;
    ss << str;

    return ss.str();
}

static void test_lazy_string_operators() {
    {
        assert(to_string("").empty());
        assert(to_string("abc") == "abc");
        assert(to_string("Hello world") == "Hello world");
        assert(to_string("Hello\0 world") == "Hello");
        assert(to_string("Hello\0 world") == "Hello\0 world");
    }

    {
        cls_07::lazy_string str;

        assert(!(str < str));
        assert(str < "a");
        assert(str < "aaaaaa");

        str += "a";
        assert(!(str < ""));
        assert(!(str < "a"));
        assert(str < "aa");
        assert(str < "b");
    }

    {
        cls_07::lazy_string left = "1";
        cls_07::lazy_string right = "0";

        assert(to_string(left + right) == "10");
        assert(to_string(right + left) == "01");

        left += left;
        right += right;
        assert(to_string(left + right) == "1100");
        assert(to_string(right + left) == "0011");
    }

    {
        cls_07::lazy_string const l_str = "Hello world!";
        std::string const str = l_str.c_str();

        for (size_t i = 0; i < l_str.get_size(); ++i) {
            assert(str[i] == l_str[i]);
        }
    }

    {
        cls_07::lazy_string original = "Hello";
        auto copy = original;

        original += "!";

        assert(to_string(original) == "Hello!");
        assert(to_string(copy) == "Hello");
    }
}

static void test_c_str_is_shared() {
    cls_07::lazy_string str;
    for (size_t i = 0; i < 100; ++i) {
        str += "another";
    }

    cls_07::lazy_string copy = str;

    assert(str.c_str() == copy.c_str());
}


int main() {
    test_lazy_string_operators();
    test_c_str_is_shared();
}