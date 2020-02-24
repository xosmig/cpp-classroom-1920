#include "range.hpp"

#include <string>
#include <vector>
#include <forward_list>
#include <cassert>
#include <map>

void test1() {
    {
        std::vector<int> v = {1, 2, 3};

        int sum = 0;
        for (auto i : cls_03::make_range(v.begin(), v.end())) {
            sum += i;
        }

        assert(sum == 6);
    }

    {
        std::vector<int> v;
        int sum = 0;

        for (auto i : cls_03::make_range(v.begin(), v.end())) {
            sum += i;
        }

        assert(sum == 0);
    }

    {
        std::vector<std::string> v = {"1", "2", "3"};
        std::string sum;

        for (auto& i : cls_03::make_range(v.begin(), v.end()).reversed()) {
            sum += i;
        }

        assert(sum == "321");
    }
}

void test2() {
    {
        std::forward_list<int> list = {1, 2, 3};
        int sum = 0;

        for (auto i : cls_03::make_range(list.begin(), list.end())) {
            sum += i;
        }

        assert(sum == 6);
    }

    {
        std::forward_list<int> list = {1, 2, 3};
        int sum = 0;

// should not compile!
//        for (auto i : cls_03::make_range(list.begin(), list.end()).reversed()) {
//            sum += i;
//        }

        assert(sum == 0);
    }
}

void test3() {
    {
        std::multimap<int, std::string> map = {{1, "Hello"}, {1, "Hi"},
                                     {2, "Goodbye"}, {2, "Bye"}};

        std::string sum;
        for (auto& i: cls_03::make_range(map.equal_range(2)).reversed()) {
            sum += i.second;
        }

        assert(sum == "ByeGoodbye"); // multimap is ordered
    }
}

#ifdef SEM_02_CLS_02_TASK_1_PRIVATE_TEST
#include "sem_02_cls_02_task_1_private_test.cpp"
#endif

int main() {
    test1();
    test2();
    test3();
#ifdef SEM_02_CLS_02_TASK_1_PRIVATE_TEST
    test_private();
#endif
}