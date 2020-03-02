#include "my_vector.h"

#include <string>
#include <cassert>

//#define TASK_2
//#define TASK_3

static void smoke_test_vector() {
    control_01::vector<std::string> vec;

    assert(vec.size() == 0);
    assert(vec.capacity() == 0);

    vec.push_back("1");
    assert(vec.size() == 1);
    assert(vec.capacity() == 1);
    assert(vec.front() == vec.back() && vec.back() == vec[0] && vec[0] == vec.at(0) && vec.at(0) == "1");

    vec.push_back("2");
    assert(vec.size() == 2);
    assert(vec.capacity() == 2);
    assert(vec.front() == "1" && vec.back() == "2" && vec[0] == "1" && vec[1] == "2");

    vec.push_back("3");
    assert(vec.size() == 3);
    assert(vec.capacity() == 4); // 2 * 2 == 4
    assert(vec.front() == "1" && vec.back() == "3" && vec[0] == "1" && vec[1] == "2" && vec[2] == "3");

    vec.pop_back();
    assert(vec.size() == 2);
    assert(vec.capacity() == 4);
    assert(vec.front() == "1" && vec.back() == "2" && vec[0] == "1" && vec[1] == "2");

    vec.push_back("4");
    assert(vec.size() == 3);
    assert(vec.capacity() == 4); // 2 * 2 == 4
    assert(vec.front() == "1" && vec.back() == "4" && vec[0] == "1" && vec[1] == "2" && vec[2] == "4");

    vec.clear();
    assert(vec.size() == 0);
    assert(vec.capacity() == 4);

    vec = control_01::vector<std::string>{};
    assert(vec.size() == 0);
    assert(vec.capacity() == 0);
}

#ifdef SEM_02_CTRL_02_PRIVATE_TEST
#include "sem_02_ctrl_02_task_1_private_test.cpp"
#endif

int main() {
    smoke_test_vector();
#ifdef SEM_02_CTRL_02_PRIVATE_TEST
    test_private();
#endif
}