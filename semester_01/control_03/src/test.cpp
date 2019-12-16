#include "linq.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <algorithm>

using std::vector;
using std::string;
using std::cout;
using std::endl;

//#define TASK_1
//#define TASK_2
//#define TASK_3
//#define TASK_3_5
//#define TASK_4

template <typename T>
T const& as_const(T const& ref) {
    return ref;
}

void test_linq_can_be_constructed_and_collected_to_vector() {
#ifdef TASK_1

    {
        vector<int> elements{1, 2, 3, 4, 5};

        auto elements_copy = control_3::from(elements).to_vector();

        assert(elements == elements_copy);
    }

    {
        vector<string> elements{"hello", "world", "lol"};

        auto elements_copy = control_3::from(elements).to_vector();

        assert(elements == elements_copy);
    }

#endif
}

void test_linq_from_copies_data_into_itself() {
#if defined(TASK_1) && !defined(TASK_4)
    {
        vector<string> elements{"hello", "world", "lol"};

        auto const elements_copy = control_3::from(elements);

        elements.emplace_back("new");

        assert(elements != elements_copy.to_vector());
    }
#endif
}

void test_you_can_check_if_any_element_is_present() {
#ifdef TASK_1

    {
        std::vector<int> int_vec{1, 2, 3, 4};
        std::vector<std::string> empty_vec;
        auto const non_empty = control_3::from<int>(int_vec);
        auto const empty = control_3::from<string>(empty_vec);

        assert(non_empty.any());
        assert(!empty.any());
    }

#endif

#ifdef TASK_2
    {
        std::vector<int> int_vec{1, 2, 3, 4, 5};
        std::vector<std::string> string_vec{"hello", "world", "lol"};

        assert(as_const(control_3::from(int_vec)).any([](int i) { return i == 5; }));

        assert(!control_3::from(string_vec).any([](string const& s) { return s == "lolo"; }));
    }

#endif
}

void test_elements_can_be_counted() {
#ifdef TASK_1

    {
        std::vector<int> int_vec{1, 2, 3, 4};
        std::vector<std::string> string_vec{"hello", "world"};
        std::vector<std::string> empty_vec;


        auto const non_empty = control_3::from<int>(int_vec);
        auto const empty = control_3::from<string>(empty_vec);
        assert(non_empty.count() == 4);
        assert(empty.count() == 0);

        assert(control_3::from(string_vec).count() == 2);
    }

#endif

#ifdef TASK_2

    {
        std::vector<int> int_vec{1, 2, 3, 4};
        std::vector<std::string> string_vec{"hello", "world", "lol"};

        auto even_numbers =
            as_const(control_3::from(int_vec))
                .count([](int i) { return i % 2 == 0; });

        assert(even_numbers == 2);

        auto words_with_length_five =
            control_3::from(string_vec)
                .count([](string const& s) { return s.size() == 5; });

        assert(words_with_length_five == 2);
    }

#endif
}


void test_select_can_transform_values() {
#ifdef TASK_3

    {
        std::vector<int> int_vec {1, 2, 3, 4};
        auto doubled =
            control_3::from(int_vec)
                .select<std::string>([](int i) { return std::to_string(i); })
                .select<std::string>([](string const& s) { return s + s; })
                .to_vector();

        assert(doubled == vector<string>({"11", "22", "33", "44"}));
    }

    {
        std::vector<int> int_vec {1, 2, 3, 4};
        auto transformed =
            control_3::from(int_vec)
                .select<int>([](int i) { return i * i; })
                .select<int>([](int i) { return i * 2; })
                .to_vector();

        assert(transformed == vector<int>({2, 8, 18, 32}));
    }

    {
////        THIS SHOULD NOT COMPILE!
////        You're not supposed to be able to change content inside of linq
//
//        vector<string> vec = {"hello", "world", "lol"};
//        auto enumeration = control_3::from<string>(vec);
//
//        auto reversed_words =
//                enumeration.select<std::string>([](std::string & s) { // <- taking by non-const reference is forbidden
//                    std::reverse(s.begin(), s.end());
//                    return s;
//                })
//                .to_vector();
    }

#endif

#ifdef TASK_3_5

    {
        std::vector<int> int_vec {1, 2, 3, 4};
        auto doubled =
            control_3::from(int_vec)
                .select([](int i) { return std::to_string(i); })
                .select([](string const& s) { return s + s; })
                .to_vector();

        assert(doubled == vector<string>({"11", "22", "33", "44"}));
    }

    {
        std::vector<int> int_vec {1, 2, 3, 4};
        auto transformed =
            control_3::from(int_vec)
                .select([](int i) { return i * i; })
                .select([](int i) { return i * 2; })
                .to_vector();

        assert(transformed == vector<int>({2, 8, 18, 32}));
    }
#endif
}

void test_where_can_filter_out_values() {
#ifdef TASK_2

    {

        std::vector<int> int_vec{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        auto filtered =
            as_const(control_3::from<int>(int_vec))
                .where([](int i) { return i % 3 != 0; })
                .where([](int i) { return i % 2 != 0; })
                .to_vector();

        assert(filtered == vector<int>({1, 5, 7}));
    }

    {
        std::vector<std::string> string_vec{"hellol", "world", "lo l", "not a single lol"};

        auto strings_without_lol =
            control_3::from<std::string>(string_vec)
                .where([](string const& s) { return s.find("lol") == string::npos; })
                .to_vector();

        assert(strings_without_lol == vector<string>({"world", "lo l"}));
    }

#endif
}

void test_select_works_together_with_where() {
#ifdef TASK_3

    {
        std::vector<std::string> string_vec{"hellol", "world", "l o l", "not a single lol"};

        auto strings_without_lol =
            control_3::from<std::string>(string_vec)
                .select<std::string>([](string s) {
                    auto is_space = [](char c) { return c == ' '; };
                    s.erase(std::remove_if(s.begin(), s.end(), is_space), s.end());
                    return s;
                })
                .where([](string const& s) { return s.find("lol") == string::npos; })
                .to_vector();

        assert(strings_without_lol == vector<string>({"world"}));
    }

    {
        std::vector<std::string> string_vec{"hellol", "1", "world", "lol"};
        auto long_strings =
            control_3::from<std::string>(string_vec)
                .select<std::pair<size_t, std::string>>([](string const& s) { return std::make_pair(s.size(), s); })
                .where([](std::pair<size_t, std::string> const& s) { return s.first >= 5; })
                .to_vector();

        assert(long_strings == (vector<std::pair<size_t, string>>({{6, "hellol"},
                                                                   {5, "world"}})));
    }

#endif

#ifdef TASK_3_5

    {
        std::vector<std::string> string_vec{"hellol", "world", "l o l", "not a single lol"};

        auto strings_without_lol =
            control_3::from<std::string>(string_vec)
                .select([](string s) {
                    auto is_space = [](char c) { return c == ' '; };
                    s.erase(std::remove_if(s.begin(), s.end(), is_space), s.end());
                    return s;
                })
                .where([](string const& s) { return s.find("lol") == string::npos; })
                .to_vector();

        assert(strings_without_lol == vector<string>({"world"}));
    }

    {
        std::vector<std::string> string_vec{"hellol", "1", "world", "lol"};
        auto long_strings =
            control_3::from<std::string>(string_vec)
                .select([](string const& s) { return std::make_pair(s.size(), s); })
                .where([](std::pair<size_t, std::string> const& s) { return s.first >= 5; })
                .to_vector();

        assert(long_strings == (vector<std::pair<size_t, string>>({{6, "hellol"},
                                                                   {5, "world"}})));
    }

#endif

}

void test_pipeline_works_lazy() {
#ifdef TASK_4

    {
        size_t counter = 0;

        std::vector<std::string> string_vec{"a", "b", "c"};

        control_3::from<string>(string_vec)
            .where([&counter](string const& c) {
                counter++;
                return c == "b";
            })
            .any();

        assert(counter == 2);
    }

    {
        size_t where_counter = 0;
        size_t any_counter = 0;

        vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8};

        control_3::from<int>(vec)
            .select([](int i) {
                return i * i;
            })
            .where([&where_counter](int i) {
                where_counter++;
                return i % 2 == 0;
            })
            .select([](int i) {
                return i * i;
            })
            .any([&any_counter](int i) {
                any_counter++;
                return i % 3 == 0;
            });

        assert(where_counter == 6);
        assert(any_counter == 3);
    }

#endif
}

int main() {
    test_linq_can_be_constructed_and_collected_to_vector();
    test_linq_from_copies_data_into_itself();
    test_elements_can_be_counted();
    test_you_can_check_if_any_element_is_present();

    test_select_can_transform_values();
    test_where_can_filter_out_values();
    test_select_works_together_with_where();

    test_pipeline_works_lazy();

    cout << "All tests passed!" << endl;
}
