#include "shared_ptr.hpp"

#include <cassert>
#include <type_traits>

static void test_weak_ptr() {
    static_assert(std::is_same<cls_10::weak_ptr<int>::element_type, int>::value, "weak ptr should define element_type");

    {
        cls_10::weak_ptr<int> ptr;

        assert(ptr.expired());
    }

    {
        cls_10::shared_ptr<int> strong_ptr;
        cls_10::weak_ptr<int> ptr{strong_ptr};

        assert(ptr.expired());

        strong_ptr.reset(new int{10});
        assert(ptr.expired());
    }

    {
        cls_10::shared_ptr<int> first{new int{10}};
        cls_10::shared_ptr<int> second{new int{20}};
        cls_10::shared_ptr<int> third{new int{30}};

        cls_10::weak_ptr<int> ptr;

        ptr = first;
        assert(!ptr.expired());
        assert(*ptr.lock() == 10);

        ptr = second;
        assert(!ptr.expired());
        assert(*ptr.lock() == 20);

        ptr = third;
        assert(!ptr.expired());
        assert(*ptr.lock() == 30);
    }

    {
        cls_10::weak_ptr<int> ptr;

        {
            cls_10::shared_ptr<int> const shared{new int{10}};

            ptr = shared;
            assert(ptr.lock());
            assert(ptr.lock().get() == shared.get());
            assert(ptr.lock().get() == shared.get());
            assert(*ptr.lock() == *shared);
        }

        assert(ptr.expired());
        assert(!ptr.lock());

        {
            cls_10::shared_ptr<int> shared{new int{20}};

            cls_10::weak_ptr<int> copy{shared};
            ptr = copy;

            if (auto lock = ptr.lock()) {
                shared.reset();
                assert(lock && *lock == 20);

                if (auto nested_lock = copy.lock()) {
                    lock.reset();
                    assert(nested_lock && *nested_lock == 20);
                } else {
                    assert(false);
                }
            } else {
                assert(false);
            }
        }
    }

    {
        cls_10::weak_ptr<int> weak_ptr;

        cls_10::shared_ptr<int> shared {weak_ptr};

        assert(!shared);

        shared.reset(new int{10});
        assert(shared);
        assert(weak_ptr.expired());

        weak_ptr = shared;
        assert(!weak_ptr.expired());
        assert(weak_ptr.lock().get() == shared.get());

        weak_ptr.reset();
        shared = weak_ptr;

        assert(!shared);
        assert(weak_ptr.expired());
    }
}

int main() {
    test_weak_ptr();
}