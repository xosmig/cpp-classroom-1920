#include "lazy_string.hpp"

#include <cassert>
#include <cstring>
#include <string>

static void test_lazy_string() {
    {
        lazy_string s1;
        lazy_string const& ref = s1;

        assert(s1.get_size() == 0);
        assert(ref.get_size() == 0);
        assert(s1.c_str()[0] == '\0');
        assert(ref.c_str()[0] == '\0');
    }

    {
        lazy_string s1 = "Hello world";
        lazy_string const s2 = s1;

        assert(s2.get_size() == s1.get_size());
        assert(s1.c_str() == s2.c_str());

        assert(s1.get_size() == sizeof("Hello world") - 1);
        assert(std::strcmp(s1.c_str(), "Hello world") == 0);
    }

    {
        lazy_string s1;
        for (size_t i = 0; i < 10; ++i) {
            s1 = concat(s1, "A");
        }

        assert(s1.get_size() == 10);
        assert(std::strcmp(s1.c_str(), "AAAAAAAAAA") == 0);
    }

    {
        lazy_string s = "Hello";
        lazy_string s_concat = concat(s, " with suffix");
        assert(std::strstr(s_concat.c_str(), s.c_str()) == s_concat.c_str());

        assert(strlen(s.c_str()) + 12 == strlen(s_concat.c_str()));
    }

    {
        std::string str {"Hello, world!"};
        lazy_string lazy_str {str.c_str() };

        for (size_t i = 0; i < str.size(); ++i) {
            assert(str[i] == lazy_str.at(i));
        }
    }
}

int main() {
    test_lazy_string();
}