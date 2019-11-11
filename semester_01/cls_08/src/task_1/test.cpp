#include "my_ostream.hpp"
#include "my_ostream_con.hpp"

#include <cassert>
#include <iostream>
#include <sstream>
#include <functional>

static void test_with_replaced_cout(std::function<void(std::ostringstream const& sout)> action) {
    std::ostringstream buffer;
	std::streambuf* coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(buffer.rdbuf());

    action(buffer);

	std::cout.rdbuf(coutbuf);
}

static void test_console_stream() {
    test_with_replaced_cout([](auto const& sout) {
        cls_08::my_ostream_con stream;
        cls_08::my_ostream& ref = stream;

        ref << "Hello!";

        assert(sout.str() == "Hello!");
    });

    test_with_replaced_cout([](auto const& sout) {
        cls_08::my_ostream_con stream;
        cls_08::my_ostream& ref = stream;

        ref << int(10) << " " << int(-10) << " " << int(1024);

        assert(sout.str() == "10 -10 1024");
    });


    test_with_replaced_cout([](auto const& sout) {
        cls_08::my_ostream_con stream;
        cls_08::my_ostream& ref = stream;

        ref << double(10.0) << " " << double(-10.1) << " " << double(1024);

        assert(sout.str() == "10 -10.1 1024");
    });
}

int main() {
    test_console_stream();

    return 0;
}