#include "shared_buffer.hpp"

#include <cassert>
#include <cstddef>
#include <cstring>
#include <type_traits>

static void test_shared_buffer() {
    {
        static_assert(!std::is_convertible_v<size_t, shared_buffer>);

        shared_buffer buffer { 10 };
        shared_buffer const ref = buffer;

        assert(buffer.get_size() == 10);
        assert(ref.get_size() == 10);

        for (size_t i = 0; i < buffer.get_size(); ++i) {
            assert(buffer.get_data()[i] == 0);
            assert(ref.get_data()[i] == 0);

            buffer.get_data()[i] = char(i);
            assert(ref.get_data()[i] == char(i));
        }
    }

    {
        static_assert(std::is_copy_constructible_v<shared_buffer>);
        static_assert(std::is_copy_assignable_v<shared_buffer>);

        shared_buffer buf1 {100};
        shared_buffer buf2 {buf1};
        shared_buffer buf3 { 10 };

        shared_buffer const& ref = buf1;

        assert(buf1.get_size() == buf2.get_size() && "Buffers should have the same size");
        assert(buf1.get_data() == buf2.get_data() && "Buffers should point to the same memory");
        assert(std::strcmp(buf1.get_data(), buf2.get_data()) == 0 && "Buffers should have equal content");

        buf3 = ref;
        assert(buf1.get_data() == buf3.get_data() && "After assignment, buf1 and buf3 should point to the same memory too");
    }

    {
        for (size_t i = 0; i < 100; ++i) {
            shared_buffer b { i };
            shared_buffer const& ref = b;
            b = ref;
        }
    }
}

int main() {
    test_shared_buffer();
}