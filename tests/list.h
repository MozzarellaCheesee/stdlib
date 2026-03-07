#pragma once
#include "./tester.h"
#include "../stdlib/list.h"
#include "stdlib/vector.h"
using stdlib::List;

inline void test_default_constructor_list() {
    stdlib::List<int> list;
    ASSERT(list.empty());
    ASSERT(list.size() == 0);
}

inline void test_initializer_list() {
    stdlib::List<int> list{1, 2, 3, 4};
    ASSERT(list.size() == 4);
    ASSERT(list.front() == 1);
    ASSERT(list.back() == 4);
}

inline void test_range_constructor_list() {
    stdlib::Vector<int> vec = {5, 6, 7};
    stdlib::List<int> list(vec.begin(), vec.end());  // или std::begin(vec), std::end(vec)
    ASSERT(list.size() == 3);
    ASSERT(*list.begin() == 5);
}

inline void test_fill_constructor_list() {
    stdlib::List<int> list(3, 42);
    ASSERT(list.size() == 3);
    ASSERT(list.front() == 42);
    ASSERT(list.back() == 42);
}

inline void test_push_front_copy_list() {
    stdlib::List<int> list;
    list.push_front(1);
    list.push_front(2);
    ASSERT(list.size() == 2);
    ASSERT(list.front() == 2);
    ASSERT(list.back() == 1);
}

inline void test_push_back_copy_list() {
    stdlib::List<int> list;
    list.push_back(1);
    list.push_back(2);
    ASSERT(list.size() == 2);
    ASSERT(list.front() == 1);
    ASSERT(list.back() == 2);
}

inline void test_push_front_move_list() {
    stdlib::List<std::string> list;
    list.push_front(std::string("hello"));
    ASSERT(list.size() == 1);
    ASSERT(list.front() == "hello");
}

inline void test_push_back_move_list() {
    stdlib::List<std::string> list;
    list.push_back(std::string("world"));
    ASSERT(list.size() == 1);
    ASSERT(list.back() == "world");
}

inline void test_pop_front_list() {
    stdlib::List<int> list{1, 2, 3};
    list.pop_front();
    ASSERT(list.size() == 2);
    ASSERT(list.front() == 2);
}

inline void test_pop_back_list() {
    stdlib::List<int> list{1, 2, 3};
    list.pop_back();
    ASSERT(list.size() == 2);
    ASSERT(list.back() == 2);
}

inline void test_insert_copy_list() {
    stdlib::List<int> list{1, 3};
    auto it = list.begin();
    ++it;
    auto inserted = list.insert(it, 2);
    ASSERT(list.size() == 3);
    ASSERT(*inserted == 2);
    ASSERT(list.front() == 1 && *inserted == 2 && list.back() == 3);
}

inline void test_insert_move_list() {
    stdlib::List<std::string> list{"a", "c"};
    auto it = list.begin();
    ++it;
    std::string s = "b";
    auto inserted = list.insert(it, std::move(s));
    ASSERT(list.size() == 3);
    ASSERT(*inserted == "b");
}

inline void test_erase_list() {
    stdlib::List<int> list{1, 2, 3};
    auto it = list.begin();
    ++it;
    auto erased = list.erase(it);
    auto end = list.end();
    ASSERT(list.size() == 2);
    ASSERT(erased == --end);
    ASSERT(list.front() == 1 && list.back() == 3);
}

inline void test_remove_list() {
    stdlib::List<int> list{1, 2, 2, 3, 2};
    list.remove(2);
    ASSERT(list.size() == 2);
    ASSERT(list.front() == 1 && list.back() == 3);
}

inline void test_access_operators_list() {
    stdlib::List<int> list{10, 20, 30};
    ASSERT(list[0] == 10);
    ASSERT(list[2] == 30);
    ASSERT(list.at(1) == 20);
    
    const auto& clist = list;
    ASSERT(clist[0] == 10);
    ASSERT(clist.at(2) == 30);
    
    ASSERT_THROWS(clist.at(5));
}

inline void test_iterators_forward_list() {
    stdlib::List<int> list{1, 2, 3, 4};
    auto it = list.begin();
    ASSERT(*it == 1);
    ++it;
    ASSERT(*it == 2);
    ++it;
    ASSERT(*it == 3);
    ++it;
    ASSERT(it == --list.end());
}

inline void test_iterators_backward_list() {
    stdlib::List<int> list{1, 2, 3};
    auto it = list.end();
    --it;
    ASSERT(*it == 3);
    --it;
    ASSERT(*it == 2);
    --it;
    ASSERT(*it == 1);
}

inline void test_const_iterators_list() {
    const stdlib::List<int> list{1, 2, 3};
    auto it = list.cbegin();
    ASSERT(*it == 1);
    ++it;
    ASSERT(*it == 2);
}

inline void test_reverse_iterators_list() {
    stdlib::List<int> list{1, 2, 3};
    auto it = list.rbegin();
    ASSERT(*it == 3);
    ++it;
    ASSERT(*it == 2);
    ++it;
    ASSERT(*it == 1);
}

inline void test_size_empty_list() {
    stdlib::List<int> list;
    ASSERT(list.empty());
    ASSERT(list.size() == 0);
    
    list.push_back(1);
    ASSERT(!list.empty());
    ASSERT(list.size() == 1);
}

inline void test_clear_list() {
    stdlib::List<int> list{1, 2, 3};
    list.clear();
    ASSERT(list.empty());
    ASSERT(list.size() == 0);
}

inline void test_copy_constructor_list() {
    stdlib::List<int> original{1, 2, 3};
    stdlib::List<int> copy(original);
    ASSERT(original == copy);
    ASSERT(copy.size() == 3);
}

inline void test_copy_assignment_list() {
    stdlib::List<int> original{1, 2};
    stdlib::List<int> copy{3, 4};
    copy = original;
    ASSERT(original == copy);
}

inline void test_move_constructor_list() {
    stdlib::List<std::string> original{"a", "b"};
    stdlib::List<std::string> moved(std::move(original));
    ASSERT(moved.size() == 2);
    ASSERT(moved.front() == "a");
    ASSERT(original.empty());
}

inline void test_move_assignment_list() {
    stdlib::List<std::string> original{"a", "b"};
    stdlib::List<std::string> target{"x"};
    target = std::move(original);
    ASSERT(target.size() == 2);
    ASSERT(target.front() == "a");
    ASSERT(original.empty());
}

inline void test_swap_list() {
    stdlib::List<int> a{1, 2};
    stdlib::List<int> b{3, 4};
    a.swap(b);
    ASSERT(a.size() == 2 && a.front() == 3);
    ASSERT(b.size() == 2 && b.front() == 1);
}

inline void test_equality_list() {
    stdlib::List<int> a{1, 2, 3};
    stdlib::List<int> b{1, 2, 3};
    stdlib::List<int> c{1, 2, 4};
    ASSERT(a == b);
    ASSERT(!(a == c));
    ASSERT(a != c);
}

inline void test_comparison_operators_list() {
    stdlib::List<int> a{1, 2};
    stdlib::List<int> b{1, 3};
    stdlib::List<int> c{1, 2, 3};
    ASSERT(a < b);
    ASSERT(a <= b);
    ASSERT(b > a);
    ASSERT(a <= c);
}

inline int list_test() {
    TestRunner tr;
    std::cout << "____________________ LIST TESTS ____________________\n";
    tr.run("default constructor", test_default_constructor_list);
    tr.run("initializer list", test_initializer_list);
    tr.run("range constructor", test_range_constructor_list);
    tr.run("fill constructor", test_fill_constructor_list);
    tr.run("push_front copy", test_push_front_copy_list);
    tr.run("push_back copy", test_push_back_copy_list);
    tr.run("push_front move", test_push_front_move_list);
    tr.run("push_back move", test_push_back_move_list);
    tr.run("pop_front", test_pop_front_list);
    tr.run("pop_back", test_pop_back_list);
    tr.run("insert copy", test_insert_copy_list);
    tr.run("insert move", test_insert_move_list);
    tr.run("erase", test_erase_list);
    tr.run("remove", test_remove_list);
    tr.run("access operators", test_access_operators_list);
    tr.run("iterators forward", test_iterators_forward_list);
    tr.run("iterators backward", test_iterators_backward_list);
    tr.run("const iterators", test_const_iterators_list);
    tr.run("reverse iterators", test_reverse_iterators_list);
    tr.run("size empty", test_size_empty_list);
    tr.run("clear", test_clear_list);
    tr.run("copy constructor", test_copy_constructor_list);
    tr.run("copy assignment", test_copy_assignment_list);
    tr.run("move constructor", test_move_constructor_list);
    tr.run("move assignment", test_move_assignment_list);
    tr.run("swap", test_swap_list);
    tr.run("equality", test_equality_list);
    tr.run("comparison operators", test_comparison_operators_list);

    tr.summary();
    return tr.exit_code();
}