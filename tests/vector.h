#pragma once
#include "./tester.h"
#include "../stdlib/vector.h"

using stdlib::Vector;

// ─── Конструкторы ───────────────────────────────────────────────────

inline void test_default_constructor_vector() {
    Vector<int> v;
    ASSERT(v.size() == 0);
    ASSERT(v.capacity() == 0);
    ASSERT(v.empty());
}

inline void test_initializer_list_vector() {
    Vector<int> v{1, 2, 3, 4, 5};
    ASSERT(v.size() == 5);
    ASSERT(v[0] == 1);
    ASSERT(v[4] == 5);
}

inline void test_fill_constructor_vector() {
    Vector<int> v(5, 42);
    ASSERT(v.size() == 5);
    for (std::size_t i = 0; i < v.size(); ++i)
        ASSERT(v[i] == 42);
}

inline void test_range_constructor_vector() {
    int arr[] = {10, 20, 30};
    Vector<int> v(arr, arr + 3);
    ASSERT(v.size() == 3);
    ASSERT(v[0] == 10);
    ASSERT(v[2] == 30);
}

inline void test_zero_fill_constructor_vector() {
    Vector<int> v(0, 42);
    ASSERT(v.size() == 0);
    ASSERT(v.empty());
}

// ─── Rule of Five ───────────────────────────────────────────────────

inline void test_copy_constructor_vector() {
    Vector<int> a{1, 2, 3};
    Vector<int> b(a);
    ASSERT(b.size() == a.size());
    ASSERT(b[0] == 1 && b[2] == 3);
    b[0] = 99;
    ASSERT(a[0] == 1); // глубокая копия
}

inline void test_move_constructor_vector() {
    Vector<int> a{1, 2, 3};
    Vector<int> b(std::move(a));
    ASSERT(b.size() == 3);
    ASSERT(b[0] == 1);
    ASSERT(a.size() == 0);
    ASSERT(a.empty());
}

inline void test_copy_assignment_vector() {
    Vector<int> a{1, 2, 3};
    Vector<int> b{9, 8};
    b = a;
    ASSERT(b.size() == 3);
    ASSERT(b[2] == 3);
    b[0] = 99;
    ASSERT(a[0] == 1); // глубокая копия
}

inline void test_move_assignment_vector() {
    Vector<int> a{1, 2, 3};
    Vector<int> b;
    b = std::move(a);
    ASSERT(b.size() == 3);
    ASSERT(b[0] == 1);
    ASSERT(a.size() == 0);
}

inline void test_self_assignment_copy_vector() {
    Vector<int> a{1, 2, 3};
    a = a;
    ASSERT(a.size() == 3);
    ASSERT(a[0] == 1);
}

inline void test_self_assignment_move_vector() {
    Vector<int> a{1, 2, 3};
    a = std::move(a);
    ASSERT(a.size() == 3);
}

// ─── Доступ к элементам ─────────────────────────────────────────────

inline void test_at_valid_vector() {
    Vector<int> v{10, 20, 30};
    ASSERT(v.at(0) == 10);
    ASSERT(v.at(2) == 30);
}

inline void test_at_out_of_range_vector() {
    Vector<int> v{1, 2, 3};
    ASSERT_THROWS(v.at(10));
    ASSERT_THROWS(v.at(3));
}

inline void test_const_at_out_of_range_vector() {
    const Vector<int> v{1, 2, 3};
    ASSERT_THROWS(v.at(5));
}

inline void test_front_back_vector() {
    Vector<int> v{1, 2, 3};
    ASSERT(v.front() == 1);
    ASSERT(v.back() == 3);
}

inline void test_front_back_single_vector() {
    Vector<int> v{42};
    ASSERT(v.front() == 42);
    ASSERT(v.back() == 42);
}

inline void test_data_vector() {
    Vector<int> v{1, 2, 3};
    int* p = v.data();
    ASSERT(p[0] == 1);
    ASSERT(p[2] == 3);
}

inline void test_const_access_vector() {
    const Vector<int> v{1, 2, 3};
    ASSERT(v[0] == 1);
    ASSERT(v.front() == 1);
    ASSERT(v.back() == 3);
    ASSERT(v.data()[1] == 2);
}

// ─── push_back / pop_back ───────────────────────────────────────────

inline void test_push_back_copy_vector() {
    Vector<int> v;
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }
    ASSERT(v.size() == 10);
    ASSERT(v[0] == 0);
    ASSERT(v[9] == 9);
}

inline void test_push_back_move_vector() {
    Vector<std::string> v;
    std::string s = "hello";
    v.push_back(std::move(s));
    ASSERT(v.size() == 1);
    ASSERT(v[0] == "hello");
    ASSERT(s.empty());
}

inline void test_pop_back_vector() {
    Vector<int> v{1, 2, 3};
    v.pop_back();
    ASSERT(v.size() == 2);
    ASSERT(v.back() == 2);
}

inline void test_pop_back_to_empty_vector() {
    Vector<int> v{1};
    v.pop_back();
    ASSERT(v.size() == 0);
    ASSERT(v.empty());
}

// ─── reserve / resize / shrink_to_fit ───────────────────────────────

inline void test_reserve_vector() {
    Vector<int> v;
    v.reserve(100);
    ASSERT(v.capacity() >= 100);
    ASSERT(v.size() == 0);
}

inline void test_reserve_no_shrink_vector() {
    Vector<int> v;
    v.reserve(100);
    std::size_t cap = v.capacity();
    v.reserve(10);
    ASSERT(v.capacity() == cap);
}

inline void test_reserve_preserves_data_vector() {
    Vector<int> v{1, 2, 3};
    v.reserve(100);
    ASSERT(v[0] == 1);
    ASSERT(v[2] == 3);
    ASSERT(v.size() == 3);
}

inline void test_resize_grow_vector() {
    Vector<int> v{1, 2, 3};
    v.resize(6, 99);
    ASSERT(v.size() == 6);
    ASSERT(v[2] == 3);
    ASSERT(v[3] == 99);
    ASSERT(v[5] == 99);
}

inline void test_resize_shrink_vector() {
    Vector<int> v{1, 2, 3, 4, 5};
    v.resize(2);
    ASSERT(v.size() == 2);
    ASSERT(v[0] == 1);
    ASSERT(v[1] == 2);
}

inline void test_resize_same_size_vector() {
    Vector<int> v{1, 2, 3};
    v.resize(3);
    ASSERT(v.size() == 3);
    ASSERT(v[2] == 3);
}

inline void test_shrink_to_fit_vector() {
    Vector<int> v;
    v.reserve(100);
    v.push_back(1);
    v.shrink_to_fit();
    ASSERT(v.capacity() == v.size());
    ASSERT(v[0] == 1);
}

// ─── clear / swap ───────────────────────────────────────────────────

inline void test_clear_vector() {
    Vector<int> v{1, 2, 3};
    v.clear();
    ASSERT(v.size() == 0);
    ASSERT(v.empty());
}

inline void test_clear_then_push_vector() {
    Vector<int> v{1, 2, 3};
    v.clear();
    v.push_back(42);
    ASSERT(v.size() == 1);
    ASSERT(v[0] == 42);
}

inline void test_swap_member_vector() {
    Vector<int> a{1, 2, 3};
    Vector<int> b{4, 5};
    a.swap(b);
    ASSERT(a.size() == 2 && a[0] == 4);
    ASSERT(b.size() == 3 && b[0] == 1);
}

inline void test_swap_free_vector() {
    Vector<int> a{1, 2, 3};
    Vector<int> b{4, 5};
    swap(a, b);
    ASSERT(a.size() == 2 && a[0] == 4);
    ASSERT(b.size() == 3 && b[0] == 1);
}

inline void test_swap_with_empty_vector() {
    Vector<int> a{1, 2, 3};
    Vector<int> b;
    a.swap(b);
    ASSERT(a.empty());
    ASSERT(b.size() == 3);
}

// ─── Операторы сравнения ────────────────────────────────────────────

inline void test_equality_vector() {
    Vector<int> a{1, 2, 3};
    Vector<int> b{1, 2, 3};
    ASSERT(a == b);
    ASSERT(!(a != b));
}

inline void test_inequality_vector() {
    Vector<int> a{1, 2, 3};
    Vector<int> b{1, 2, 4};
    ASSERT(a != b);
    ASSERT(!(a == b));
}

inline void test_different_sizes_not_equal_vector() {
    Vector<int> a{1, 2, 3};
    Vector<int> b{1, 2};
    ASSERT(a != b);
}

inline void test_less_than_vector() {
    Vector<int> a{1, 2, 3};
    Vector<int> b{1, 2, 4};
    Vector<int> c{1, 2};
    ASSERT(a < b);
    ASSERT(c < a);
    ASSERT(!(b < a));
}

inline void test_comparison_operators_vector() {
    Vector<int> a{1, 2, 3};
    Vector<int> b{1, 2, 4};
    ASSERT(a <= b);
    ASSERT(b >= a);
    ASSERT(b > a);
    ASSERT(a <= a);
    ASSERT(a >= a);
    ASSERT(!(a > a));
    ASSERT(!(a < a));
}

// ─── Итераторы ──────────────────────────────────────────────────────

inline void test_range_for_vector() {
    Vector<int> v{1, 2, 3, 4, 5};
    int sum = 0;
    for (int x : v) sum += x;
    ASSERT(sum == 15);
}

inline void test_iterator_mutation_vector() {
    Vector<int> v{1, 2, 3};
    for (auto it = v.begin(); it != v.end(); ++it)
        *it *= 2;
    ASSERT(v[0] == 2 && v[1] == 4 && v[2] == 6);
}

inline void test_reverse_iterators_vector() {
    Vector<int> v{1, 2, 3};
    auto it = v.rbegin();
    ASSERT(*it == 3); ++it;
    ASSERT(*it == 2); ++it;
    ASSERT(*it == 1);
}

inline void test_const_iterators_vector() {
    const Vector<int> v{1, 2, 3};
    int sum = 0;
    for (auto it = v.cbegin(); it != v.cend(); ++it)
        sum += *it;
    ASSERT(sum == 6);
}

// ─── Стресс ─────────────────────────────────────────────────────────

inline void test_many_push_backs_vector() {
    Vector<int> v;
    for (int i = 0; i < 100000; ++i)
        v.push_back(i);
    ASSERT(v.size() == 100000);
    ASSERT(v[0] == 0);
    ASSERT(v[99999] == 99999);
}

inline void test_push_pop_interleaved_vector() {
    Vector<int> v;
    for (int i = 0; i < 1000; ++i) {
        v.push_back(i);
        if (i % 2 == 0) v.pop_back();
    }
    ASSERT(v.size() == 500);
}

// ─── main ────────────────────────────────────────────────────────────

inline int vector_test() {
    TestRunner tr;

    std::cout << "____________________ VECTOR TESTS ____________________\n";
    tr.run("default constructor",       test_default_constructor_vector);
    tr.run("initializer_list",          test_initializer_list_vector);
    tr.run("fill constructor",          test_fill_constructor_vector);
    tr.run("range constructor",         test_range_constructor_vector);
    tr.run("zero fill constructor",     test_zero_fill_constructor_vector);
    tr.run("copy constructor",          test_copy_constructor_vector);
    tr.run("move constructor",          test_move_constructor_vector);
    tr.run("copy assignment",           test_copy_assignment_vector);
    tr.run("move assignment",           test_move_assignment_vector);
    tr.run("self assignment copy",      test_self_assignment_copy_vector);
    tr.run("self assignment move",      test_self_assignment_move_vector);
    tr.run("at valid",                  test_at_valid_vector);
    tr.run("at out of range",           test_at_out_of_range_vector);
    tr.run("const at out of range",     test_const_at_out_of_range_vector);
    tr.run("front/back",                test_front_back_vector);
    tr.run("front/back single",         test_front_back_single_vector);
    tr.run("data()",                    test_data_vector);
    tr.run("const access",              test_const_access_vector);
    tr.run("push_back copy",            test_push_back_copy_vector);
    tr.run("push_back move",            test_push_back_move_vector);
    tr.run("pop_back",                  test_front_back_vector);
    tr.run("pop_back to empty",         test_pop_back_to_empty_vector);
    tr.run("reserve",                   test_reserve_vector);
    tr.run("reserve no shrink",         test_reserve_no_shrink_vector);
    tr.run("reserve preserves data",    test_reserve_preserves_data_vector);
    tr.run("resize grow",               test_resize_grow_vector);
    tr.run("resize shrink",             test_resize_shrink_vector);
    tr.run("resize same size",          test_resize_same_size_vector);
    tr.run("shrink_to_fit",             test_shrink_to_fit_vector);
    tr.run("clear",                     test_clear_vector);
    tr.run("clear then push",           test_clear_then_push_vector);
    tr.run("swap member",               test_swap_member_vector);
    tr.run("swap free",                 test_swap_free_vector);
    tr.run("swap with empty",           test_swap_with_empty_vector);
    tr.run("equality",                  test_equality_vector);
    tr.run("inequality",                test_inequality_vector);
    tr.run("different sizes not equal", test_different_sizes_not_equal_vector);
    tr.run("less than",                 test_less_than_vector);
    tr.run("comparison operators",      test_comparison_operators_vector);
    tr.run("range-for",                 test_range_for_vector);
    tr.run("iterator mutation",         test_iterator_mutation_vector);
    tr.run("reverse iterators",         test_reverse_iterators_vector);
    tr.run("const iterators",           test_const_iterators_vector);
    tr.run("many push_backs",           test_many_push_backs_vector);
    tr.run("push/pop interleaved",      test_push_pop_interleaved_vector);

    tr.summary();
    return tr.exit_code();
}
