#pragma once
#include "./tester.h"
#include "../stdlib/stack.h"

using stdlib::Stack;


inline void test_default_constructor_stack() {
    Stack<int> s;
    ASSERT(s.empty());
    ASSERT(s.len() == 0);
}

inline void test_push_pop_int_stack() {
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    ASSERT(s.len() == 3);
    ASSERT(s.peek() == 3);
    ASSERT(s.pop() == 3);
    ASSERT(s.len() == 2);
    ASSERT(s.peek() == 2);
    ASSERT(s.pop() == 2);
    ASSERT(s.pop() == 1);
    ASSERT(s.empty());
}

inline void test_push_pop_string_stack_stack() {
    Stack<std::string> s;
    s.push("first");
    s.push("second");
    ASSERT(s.len() == 2);
    ASSERT(s.peek() == "second");
    ASSERT(s.pop() == "second");
    ASSERT(s.pop() == "first");
}

inline void test_empty_pop_stack() {
    Stack<int> s;
    ASSERT_THROWS(s.pop()); // должен бросить исключение
}

inline void test_empty_peek_stack() {
    Stack<int> s;
    ASSERT_THROWS(s.peek()); // должен бросить исключение
}

inline void test_move_constructor_stack() {
    Stack<int> a;
    a.push(1); a.push(2);
    Stack<int> b(std::move(a));
    ASSERT(b.len() == 2);
    ASSERT(b.peek() == 2);
    ASSERT(a.empty());
}

inline void test_move_assignment_stack() {
    Stack<int> a;
    a.push(1); a.push(2);
    Stack<int> b;
    b.push(99);
    b = std::move(a);
    ASSERT(b.len() == 2);
    ASSERT(b.peek() == 2);
    ASSERT(a.empty());
    ASSERT(b.len() == 2); // b не пустая
}

inline void test_copy_constructor_stack() {
    Stack<int> a;
    a.push(1); a.push(2);
    Stack<int> b(a);
    ASSERT(b.len() == 2);
    ASSERT(b.peek() == 2);
    b.pop();
    ASSERT(a.len() == 2); // глубокая копия
}

inline void test_copy_assignment() {
    Stack<int> a;
    a.push(1); a.push(2);
    Stack<int> b;
    b.push(99);
    b = a;
    ASSERT(b.len() == 2);
    ASSERT(b.peek() == 2);
    b.pop();
    ASSERT(a.len() == 2); // глубокая копия
}

inline void test_find_empty_stack() {
    Stack<int> s;
    auto indices = s.find(42);
    ASSERT(indices.empty());
}

inline void test_find_not_found_stack() {
    Stack<int> s;
    s.push(1); s.push(3); s.push(5);
    auto indices = s.find(2);
    ASSERT(indices.empty());
}

inline void test_find_one_stack() {
    Stack<int> s;
    s.push(1); s.push(2); s.push(3); s.push(2);
    auto indices = s.find(2);
    ASSERT(indices.size() == 2);
    ASSERT(indices[0] == 1); // от низа стека: индекс 1
    ASSERT(indices[1] == 3);
}

inline void test_find_all_stack() {
    Stack<int> s;
    s.push(1); s.push(2); s.push(2); s.push(3); s.push(2);
    auto indices = s.find(2);
    ASSERT(indices.size() == 3);
    ASSERT(indices[0] == 1);
    ASSERT(indices[1] == 2);
    ASSERT(indices[2] == 4);
}

inline void test_initial_capacity_stack() {
    Stack<int> s(32);
    ASSERT(s.len() == 0);
    ASSERT(s.empty());
    for (int i = 0; i < 40; ++i)
        s.push(i);
    ASSERT(s.len() == 40);
}

inline void test_len_after_operations_stack() {
    Stack<int> s;
    ASSERT(s.len() == 0);
    s.push(1);
    ASSERT(s.len() == 1);
    s.pop();
    ASSERT(s.len() == 0);
    s.push(2); s.push(3);
    ASSERT(s.len() == 2);
}

inline int stack_test() {
    TestRunner tr;

    std::cout << "____________________ STACK TESTS ____________________\n";
    tr.run("default constructor", test_default_constructor_stack);
    tr.run("push/pop int",        test_push_pop_int_stack);
    tr.run("push/pop string",     test_push_pop_int_stack);
    tr.run("empty pop",           test_empty_pop_stack);
    tr.run("empty peek",          test_empty_peek_stack);
    tr.run("move constructor",    test_move_constructor_stack);
    tr.run("move assignment",     test_move_assignment_stack);
    tr.run("copy constructor",    test_copy_constructor_stack);
    tr.run("copy assignment",     test_move_assignment_stack);
    tr.run("find empty",          test_find_empty_stack);
    tr.run("find not found",      test_find_not_found_stack);
    tr.run("find one",            test_find_one_stack);
    tr.run("find all",            test_find_all_stack);
    tr.run("initial capacity",    test_initial_capacity_stack);
    tr.run("len after ops",       test_len_after_operations_stack);

    tr.summary();
    return tr.exit_code();
}
