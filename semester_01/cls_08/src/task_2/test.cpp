#include "my_ostream.hpp"
#include <my_ostream_file.hpp>

#include <cassert>
#include <iostream>
#include <fstream>
#include <type_traits>

static std::string read_file_content(std::string const& name) {
    std::fstream file{name};

    return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}

static_assert(std::is_abstract<my_ostream>::value, "my_ostream should be abstract class!");
static_assert(!std::is_copy_constructible<my_ostream_file>::value, "You shouldn't be able to copy my_ostream_file!");
static_assert(!std::is_copy_assignable<my_ostream_file>::value, "You shouldn't be able to copy my_ostream_file!");

static void test_file_stream() {
    const char* file_name = "tmp.txt";

    {
        std::remove(file_name);

        {
            cls_08::my_ostream_file file_stream{file_name};
            cls_08::my_ostream& ref = file_stream;

            ref << "Hello there!";
        }

        assert(read_file_content(file_name) == "Hello there!");
    }

    {
        std::remove(file_name);

        {
            cls_08::my_ostream_file file_stream{file_name};
            cls_08::my_ostream& ref = file_stream;

            ref << 1024;
        }

        assert(read_file_content(file_name) == "1024");
    }

    {
        std::remove(file_name);

        {
            cls_08::my_ostream_file file_stream{file_name};
            cls_08::my_ostream& ref = file_stream;

            ref << 12.345;
        }

        assert(read_file_content(file_name) == "12.345");
    }
}

int main() {
    test_file_stream();

    return 0;
}