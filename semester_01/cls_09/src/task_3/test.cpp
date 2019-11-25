#include "priority_queue.hpp"

#include <vector>
#include <functional>
#include <cassert>

static void test_priority_queue() {
    {
        cls_09::priority_queue<size_t> queue;
        for (size_t i = 0; i < 10; ++i)
        {
            queue.push(i);
        }

        for (int i = 9; i >= 0; --i)
        {
            assert(queue.front() == static_cast<size_t>(i));
            queue.pop();
        }
    }
}

int main() {
    test_priority_queue();
}