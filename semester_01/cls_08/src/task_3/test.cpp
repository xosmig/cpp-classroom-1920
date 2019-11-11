#include "my_ostream.hpp"
#include "my_ostream_con.hpp"
#include "my_ostream_file.hpp"
#include "my_ostream_combo.hpp"

#include <functional>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cassert>

static void test_with_replaced_cout(std::function<void(std::ostringstream const& sout)> const& action) {
    std::ostringstream buffer;
    std::streambuf* coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(buffer.rdbuf());

    action(buffer);

    std::cout.rdbuf(coutbuf);
}

static std::string read_file_content(std::string const& name) {
    std::fstream file{name};

    return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}

static void test_combo_stream() {
    const char* f1_file = "f1.txt";
    const char* f2_file = "f2.txt";

    auto clear_files = [=]() {
        std::remove(f1_file);
        std::remove(f2_file);
    };

    {
        clear_files();

        {
            cls_08::my_ostream_combo combo{new cls_08::my_ostream_file{f1_file}, new cls_08::my_ostream_file{f2_file}};

            combo << "Hello!" << 1 << " " << 2.3;
        }

        assert(read_file_content(f1_file) == read_file_content(f2_file));
        assert(read_file_content(f1_file) == "Hello!1 2.3");
    }

    {
        clear_files();

        test_with_replaced_cout([=](auto const& sout) {
            {
                cls_08::my_ostream_combo combo{
                    new cls_08::my_ostream_combo{
                        new cls_08::my_ostream_con{},
                        new cls_08::my_ostream_file{f1_file}
                    },
                    new cls_08::my_ostream_file{f2_file}
                };

                combo << "Hello!" << 1 << " " << 2.3;
            }

            assert(read_file_content(f1_file) == read_file_content(f2_file));
            assert(read_file_content(f2_file) == sout.str());
        });
    }
}

int main() {
    test_combo_stream();

    return 0;
}