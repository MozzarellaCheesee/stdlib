#include <cassert>
#include <iostream>
#include <string>

#include "./tester.cpp"
#include "../stdlib/vector.h"

using stdlib::Vector;

// ─── Конструкторы ───────────────────────────────────────────────────

void test_default_constructor() {
    Vector<int> v;
    ASSERT(v.size() == 0);
    ASSERT(v.capacity() == 0);
    ASSERT(v.empty());
}

void test_initializer_list() {
    Vector<int> v{1, 2, 3, 4, 5};
    ASSERT(v.size() == 5);
    ASSERT(v[0] == 1);
    ASSERT(v[4] == 5);
}

void test_fill_constructor() {
    Vector<int> v(5, 42);
    ASSERT(v.size() == 5);
    for (std::size_t i = 0; i < v.size(); ++i)
        ASSERT(v[i] == 42);
}

void test_range_constructor() {
    int arr[] = {10, 20, 30};
    Vector<int> v(arr, arr + 3);
    ASSERT(v.size() == 3);
    ASSERT(v[0] == 10);
    ASSERT(v[2] == 30);
}

void test_zero_fill_constructor() {
    Vector<int> v(0, 42);
    ASSERT(v.size() == 0);
    ASSERT(v.empty());
}

// ─── Rule of Five ───────────────────────────────────────────────────

void test_copy_constructor() {
    Vector<int> a{1, 2, 3};
    Vector<int> b(a);
    ASSERT(b.size() == a.size());
    ASSERT(b[0] == 1 && b[2] == 3);
    b[0] = 99;
    ASSERT(a[0] == 1); // глубокая копия
}

void test_move_constructor() {
    Vector<int> a{1, 2, 3};
    Vector<int> b(std::move(a));
    ASSERT(b.size() == 3);
    ASSERT(b[0] == 1);
    ASSERT(a.size() == 0);
    ASSERT(a.empty());
}

void test_copy_assignment() {
    Vector<int> a{1, 2, 3};
    Vector<int> b{9, 8};
    b = a;
    ASSERT(b.size() == 3);
    ASSERT(b[2] == 3);
    b[0] = 99;
    ASSERT(a[0] == 1); // глубокая копия
}

void test_move_assignment() {
    Vector<int> a{1, 2, 3};
    Vector<int> b;
    b = std::move(a);
    ASSERT(b.size() == 3);
    ASSERT(b[0] == 1);
    ASSERT(a.size() == 0);
}

void test_self_assignment_copy() {
    Vector<int> a{1, 2, 3};
    a = a;
    ASSERT(a.size() == 3);
    ASSERT(a[0] == 1);
}

void test_self_assignment_move() {
    Vector<int> a{1, 2, 3};
    a = std::move(a);
    ASSERT(a.size() == 3);
}

// ─── Доступ к элементам ─────────────────────────────────────────────

void test_at_valid() {
    Vector<int> v{10, 20, 30};
    ASSERT(v.at(0) == 10);
    ASSERT(v.at(2) == 30);
}

void test_at_out_of_range() {
    Vector<int> v{1, 2, 3};
    ASSERT_THROWS(v.at(10));
    ASSERT_THROWS(v.at(3));
}

void test_const_at_out_of_range() {
    const Vector<int> v{1, 2, 3};
    ASSERT_THROWS(v.at(5));
}

void test_front_back() {
    Vector<int> v{1, 2, 3};
    ASSERT(v.front() == 1);
    ASSERT(v.back() == 3);
}

void test_front_back_single() {
    Vector<int> v{42};
    ASSERT(v.front() == 42);
    ASSERT(v.back() == 42);
}

void test_data() {
    Vector<int> v{1, 2, 3};
    int* p = v.data();
    ASSERT(p[0] == 1);
    ASSERT(p[2] == 3);
}

void test_const_access() {
    const Vector<int> v{1, 2, 3};
    ASSERT(v[0] == 1);
    ASSERT(v.front() == 1);
    ASSERT(v.back() == 3);
    ASSERT(v.data()[1] == 2);
}

// ─── push_back / pop_back ───────────────────────────────────────────

void test_push_back_copy() {
    Vector<int> v;
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }
    ASSERT(v.size() == 10);
    ASSERT(v[0] == 0);
    ASSERT(v[9] == 9);
}

void test_push_back_move() {
    Vector<std::string> v;
    std::string s = "hello";
    v.push_back(std::move(s));
    ASSERT(v.size() == 1);
    ASSERT(v[0] == "hello");
    ASSERT(s.empty());
}

void test_pop_back() {
    Vector<int> v{1, 2, 3};
    v.pop_back();
    ASSERT(v.size() == 2);
    ASSERT(v.back() == 2);
}

void test_pop_back_to_empty() {
    Vector<int> v{1};
    v.pop_back();
    ASSERT(v.size() == 0);
    ASSERT(v.empty());
}

// ─── reserve / resize / shrink_to_fit ───────────────────────────────

void test_reserve() {
    Vector<int> v;
    v.reserve(100);
    ASSERT(v.capacity() >= 100);
    ASSERT(v.size() == 0);
}

void test_reserve_no_shrink() {
    Vector<int> v;
    v.reserve(100);
    std::size_t cap = v.capacity();
    v.reserve(10);
    ASSERT(v.capacity() == cap);
}

void test_reserve_preserves_data() {
    Vector<int> v{1, 2, 3};
    v.reserve(100);
    ASSERT(v[0] == 1);
    ASSERT(v[2] == 3);
    ASSERT(v.size() == 3);
}

void test_resize_grow() {
    Vector<int> v{1, 2, 3};
    v.resize(6, 99);
    ASSERT(v.size() == 6);
    ASSERT(v[2] == 3);
    ASSERT(v[3] == 99);
    ASSERT(v[5] == 99);
}

void test_resize_shrink() {
    Vector<int> v{1, 2, 3, 4, 5};
    v.resize(2);
    ASSERT(v.size() == 2);
    ASSERT(v[0] == 1);
    ASSERT(v[1] == 2);
}

void test_resize_same_size() {
    Vector<int> v{1, 2, 3};
    v.resize(3);
    ASSERT(v.size() == 3);
    ASSERT(v[2] == 3);
}

void test_shrink_to_fit() {
    Vector<int> v;
    v.reserve(100);
    v.push_back(1);
    v.shrink_to_fit();
    ASSERT(v.capacity() == v.size());
    ASSERT(v[0] == 1);
}

// ─── clear / swap ───────────────────────────────────────────────────

void test_clear() {
    Vector<int> v{1, 2, 3};
    v.clear();
    ASSERT(v.size() == 0);
    ASSERT(v.empty());
}

void test_clear_then_push() {
    Vector<int> v{1, 2, 3};
    v.clear();
    v.push_back(42);
    ASSERT(v.size() == 1);
    ASSERT(v[0] == 42);
}

void test_swap_member() {
    Vector<int> a{1, 2, 3};
    Vector<int> b{4, 5};
    a.swap(b);
    ASSERT(a.size() == 2 && a[0] == 4);
    ASSERT(b.size() == 3 && b[0] == 1);
}

void test_swap_free() {
    Vector<int> a{1, 2, 3};
    Vector<int> b{4, 5};
    swap(a, b);
    ASSERT(a.size() == 2 && a[0] == 4);
    ASSERT(b.size() == 3 && b[0] == 1);
}

void test_swap_with_empty() {
    Vector<int> a{1, 2, 3};
    Vector<int> b;
    a.swap(b);
    ASSERT(a.empty());
    ASSERT(b.size() == 3);
}

// ─── Операторы сравнения ────────────────────────────────────────────

void test_equality() {
    Vector<int> a{1, 2, 3};
    Vector<int> b{1, 2, 3};
    ASSERT(a == b);
    ASSERT(!(a != b));
}

void test_inequality() {
    Vector<int> a{1, 2, 3};
    Vector<int> b{1, 2, 4};
    ASSERT(a != b);
    ASSERT(!(a == b));
}

void test_different_sizes_not_equal() {
    Vector<int> a{1, 2, 3};
    Vector<int> b{1, 2};
    ASSERT(a != b);
}

void test_less_than() {
    Vector<int> a{1, 2, 3};
    Vector<int> b{1, 2, 4};
    Vector<int> c{1, 2};
    ASSERT(a < b);
    ASSERT(c < a);
    ASSERT(!(b < a));
}

void test_comparison_operators() {
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

void test_range_for() {
    Vector<int> v{1, 2, 3, 4, 5};
    int sum = 0;
    for (int x : v) sum += x;
    ASSERT(sum == 15);
}

void test_iterator_mutation() {
    Vector<int> v{1, 2, 3};
    for (auto it = v.begin(); it != v.end(); ++it)
        *it *= 2;
    ASSERT(v[0] == 2 && v[1] == 4 && v[2] == 6);
}

void test_reverse_iterators() {
    Vector<int> v{1, 2, 3};
    auto it = v.rbegin();
    ASSERT(*it == 3); ++it;
    ASSERT(*it == 2); ++it;
    ASSERT(*it == 1);
}

void test_const_iterators() {
    const Vector<int> v{1, 2, 3};
    int sum = 0;
    for (auto it = v.cbegin(); it != v.cend(); ++it)
        sum += *it;
    ASSERT(sum == 6);
}

// ─── Стресс ─────────────────────────────────────────────────────────

void test_many_push_backs() {
    Vector<int> v;
    for (int i = 0; i < 100000; ++i)
        v.push_back(i);
    ASSERT(v.size() == 100000);
    ASSERT(v[0] == 0);
    ASSERT(v[99999] == 99999);
}

void test_push_pop_interleaved() {
    Vector<int> v;
    for (int i = 0; i < 1000; ++i) {
        v.push_back(i);
        if (i % 2 == 0) v.pop_back();
    }
    ASSERT(v.size() == 500);
}

// ─── main ────────────────────────────────────────────────────────────

int main() {
    TestRunner tr;

    std::cout << "____________________ VECTOR TESTS ____________________\n";

    std::cout << "[ Constructors ]\n";
    tr.run("default constructor",       test_default_constructor);
    tr.run("initializer_list",          test_initializer_list);
    tr.run("fill constructor",          test_fill_constructor);
    tr.run("range constructor",         test_range_constructor);
    tr.run("zero fill constructor",     test_zero_fill_constructor);

    std::cout << "\n[ Rule of Five ]\n";
    tr.run("copy constructor",          test_copy_constructor);
    tr.run("move constructor",          test_move_constructor);
    tr.run("copy assignment",           test_copy_assignment);
    tr.run("move assignment",           test_move_assignment);
    tr.run("self assignment copy",      test_self_assignment_copy);
    tr.run("self assignment move",      test_self_assignment_move);

    std::cout << "\n[ Element access ]\n";
    tr.run("at valid",                  test_at_valid);
    tr.run("at out of range",           test_at_out_of_range);
    tr.run("const at out of range",     test_const_at_out_of_range);
    tr.run("front/back",                test_front_back);
    tr.run("front/back single",         test_front_back_single);
    tr.run("data()",                    test_data);
    tr.run("const access",              test_const_access);

    std::cout << "\n[ push_back / pop_back ]\n";
    tr.run("push_back copy",            test_push_back_copy);
    tr.run("push_back move",            test_push_back_move);
    tr.run("pop_back",                  test_pop_back);
    tr.run("pop_back to empty",         test_pop_back_to_empty);

    std::cout << "\n[ reserve / resize / shrink_to_fit ]\n";
    tr.run("reserve",                   test_reserve);
    tr.run("reserve no shrink",         test_reserve_no_shrink);
    tr.run("reserve preserves data",    test_reserve_preserves_data);
    tr.run("resize grow",               test_resize_grow);
    tr.run("resize shrink",             test_resize_shrink);
    tr.run("resize same size",          test_resize_same_size);
    tr.run("shrink_to_fit",             test_shrink_to_fit);

    std::cout << "\n[ clear / swap ]\n";
    tr.run("clear",                     test_clear);
    tr.run("clear then push",           test_clear_then_push);
    tr.run("swap member",               test_swap_member);
    tr.run("swap free",                 test_swap_free);
    tr.run("swap with empty",           test_swap_with_empty);

    std::cout << "\n[ Comparison operators ]\n";
    tr.run("equality",                  test_equality);
    tr.run("inequality",                test_inequality);
    tr.run("different sizes not equal", test_different_sizes_not_equal);
    tr.run("less than",                 test_less_than);
    tr.run("comparison operators",      test_comparison_operators);

    std::cout << "\n[ Iterators ]\n";
    tr.run("range-for",                 test_range_for);
    tr.run("iterator mutation",         test_iterator_mutation);
    tr.run("reverse iterators",         test_reverse_iterators);
    tr.run("const iterators",           test_const_iterators);

    std::cout << "\n[ Stress ]\n";
    tr.run("many push_backs",           test_many_push_backs);
    tr.run("push/pop interleaved",      test_push_pop_interleaved);

    tr.summary();
    return tr.exit_code();
}
