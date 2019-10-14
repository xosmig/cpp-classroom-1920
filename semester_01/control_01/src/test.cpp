#include <cassert>
#include <cstring>
#include "network.hpp"

// #define PART_1
// #define PART_2
// #define PART_2_2
// #define PART_3

void test_part_1() {
#ifdef PART_1
    // simple calls
    {
        Post* post1 = create_post("u1", "m1");
        Post* post2 = create_post("u2", "m2", post1);

        assert(previous(post2) == post1);
        assert(previous(post1) == nullptr);

        assert(std::strcmp(get_user(post1), "u1") == 0);
        assert(std::strcmp(get_text(post2), "m2") == 0);

        destroy_posts(post2);
    }

    // don't forget to copy
    {
        char buff[] = "Hello msg";
        Post* post = create_post("u1", buff);

        buff[0] = 'A';
        assert(std::strcmp(get_text(post), buff) != 0); // Hello != Aello

        destroy_posts(post);
    }
#endif
}

void test_part_2() {
#ifdef PART_2
    // simple case
    {
        Post* post = create_post("u1", "m1");
        Post* result = remove_by_content(post, "1");

        assert(result == nullptr);

        destroy_posts(result);
    };

    // harder case
    {
        Post* post1 = create_post("u1", "my cow");
        Post* post2 = create_post("u2", "cow is so", post1);
        Post* post3 = create_post("u2", "is so my", post2);
        Post* result = remove_by_content(post3, "my");

        assert(result == post2);
        assert(previous(result) == nullptr);

        destroy_posts(result);
    };
#endif
}

void test_part_2_2() {
#ifdef PART_2_2
    {
        Post* post = create_post("u1", "m1");
        Post* result = remove_if(post, [&](Post const* curr) { return curr == post; });

        assert(result == nullptr);

        destroy_posts(result);
    };
#endif
}

void test_part_3() {
#ifdef PART_3
    Post* post1 = create_post("u1", "m1");
    Post* post2 = create_post("u1", "m2");
    Post* post3 = create_post("u1", "m2", post1);
    Post* post4 = create_post("u1", "m2", post2);

    Post* result = merge(post3, post4);

    assert(result == post4);
    assert(previous(result) == post3);
    assert(previous(previous(result)) == post2);
    assert(previous(previous(previous(result))) == post1);
    assert(previous(previous(previous(previous(result)))) == nullptr);

    destroy_posts(result);
#endif
}

int main() {
    test_part_1();
    test_part_2();
    test_part_2_2();
    test_part_3();
    return 0;
}