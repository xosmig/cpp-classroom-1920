#include "scoped_ptr.hpp"

#include <cassert>
#include <string>
#include <type_traits>

static void test_scoped_ptr() {
    static_assert(
        !std::is_convertible<int*, cls_10::scoped_ptr<int>>::value,
        "scoped ptr should not have implicit constructor from pointer!"
    );

    static_assert(
        !std::is_copy_constructible<cls_10::scoped_ptr<int>>::value,
        "scoped ptr should not be copiable"
    );

    static_assert(
        !std::is_move_constructible<cls_10::scoped_ptr<int>>::value,
        "scoped ptr should not be movable"
    );

    static_assert(
        !std::is_copy_assignable<cls_10::scoped_ptr<int>>::value,
        "scoped ptr should not be copiable by operator="
    );

    static_assert(
        !std::is_move_assignable<cls_10::scoped_ptr<int>>::value,
        "scoped ptr should not be movable by operator="
    );

    static_assert(
        std::is_same<cls_10::scoped_ptr<int>::element_type, int>::value,
        "scoped ptr should contain element_type"
    );

    static_assert(
        std::is_constructible<bool, cls_10::scoped_ptr<int>>::value // explicit conversion
        && !std::is_convertible<cls_10::scoped_ptr<int>, bool>::value, // implicit conversion
        "scoped ptr should convertible to the bool, but not implicitly"
    );

    {
        cls_10::scoped_ptr<int> empty_ptr;

        assert(!empty_ptr);
        assert(empty_ptr.get() == nullptr);
    }

    {
        struct entity {
            int f1;
            std::string f2;
        };

        static_assert(
            std::is_same<cls_10::scoped_ptr<entity>::element_type, entity>::value,
            "scoped ptr should contain element_type"
        );

        cls_10::scoped_ptr<entity> const ptr{new entity{10, "hello"}};

        assert(ptr->f1 == 10);
        assert(ptr->f2 == "hello");

        assert((*ptr).f1 == 10);
        assert((*ptr).f2 == "hello");

        assert(ptr.get()->f1 == 10);
        assert(ptr.get()->f2 == "hello");
    }

    {
        cls_10::scoped_ptr<int> ptr{new int{10}};
        assert(*ptr == 10);
        assert(ptr);

        ptr.reset();
        assert(ptr.get() == nullptr);
        assert(!ptr);

        ptr.reset(new int{20});
        assert(*ptr == 20);
    }
    
    {
        int* i = new int{10};
        cls_10::scoped_ptr<int> ptr{i};
        
        assert(i == ptr.release());
        
        delete i;
    }
}

int main() {
    test_scoped_ptr();
}