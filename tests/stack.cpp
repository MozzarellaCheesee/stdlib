#include <cassert>
#include <iostream>

#include "./tester.cpp"
#include "../stdlib/stack.h"

using stdlib::Stack;


void test_default_constructor() {
    Stack<int> s;
    ASSERT(s.empty());
    ASSERT(s.len() == 0);
}

void test_push_pop_int() {
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

void test_push_pop_string() {
    Stack<std::string> s;
    s.push("first");
    s.push("second");
    ASSERT(s.len() == 2);
    ASSERT(s.peek() == "second");
    ASSERT(s.pop() == "second");
    ASSERT(s.pop() == "first");
}

void test_empty_pop() {
    Stack<int> s;
    ASSERT_THROWS(s.pop()); // должен бросить исключение
}

void test_empty_peek() {
    Stack<int> s;
    ASSERT_THROWS(s.peek()); // должен бросить исключение
}

void test_move_constructor() {
    Stack<int> a;
    a.push(1); a.push(2);
    Stack<int> b(std::move(a));
    ASSERT(b.len() == 2);
    ASSERT(b.peek() == 2);
    ASSERT(a.empty());
}

void test_move_assignment() {
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

void test_copy_constructor() {
    Stack<int> a;
    a.push(1); a.push(2);
    Stack<int> b(a);
    ASSERT(b.len() == 2);
    ASSERT(b.peek() == 2);
    b.pop();
    ASSERT(a.len() == 2); // глубокая копия
}

void test_copy_assignment() {
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

void test_find_empty() {
    Stack<int> s;
    auto indices = s.find(42);
    ASSERT(indices.empty());
}

void test_find_not_found() {
    Stack<int> s;
    s.push(1); s.push(3); s.push(5);
    auto indices = s.find(2);
    ASSERT(indices.empty());
}

void test_find_one() {
    Stack<int> s;
    s.push(1); s.push(2); s.push(3); s.push(2);
    auto indices = s.find(2);
    ASSERT(indices.size() == 2);
    ASSERT(indices[0] == 1); // от низа стека: индекс 1
    ASSERT(indices[1] == 3);
}

void test_find_all() {
    Stack<int> s;
    s.push(1); s.push(2); s.push(2); s.push(3); s.push(2);
    auto indices = s.find(2);
    ASSERT(indices.size() == 3);
    ASSERT(indices[0] == 1);
    ASSERT(indices[1] == 2);
    ASSERT(indices[2] == 4);
}

void test_initial_capacity() {
    Stack<int> s(32);
    ASSERT(s.len() == 0);
    ASSERT(s.empty());
    for (int i = 0; i < 40; ++i)
        s.push(i);
    ASSERT(s.len() == 40);
}

void test_len_after_operations() {
    Stack<int> s;
    ASSERT(s.len() == 0);
    s.push(1);
    ASSERT(s.len() == 1);
    s.pop();
    ASSERT(s.len() == 0);
    s.push(2); s.push(3);
    ASSERT(s.len() == 2);
}

int main() {
    TestRunner tr;

    std::cout << "____________________ STACK TESTS ____________________\n";

    std::cout << "[ Basic ]\n";
    tr.run("default constructor", test_default_constructor);
    tr.run("push/pop int",        test_push_pop_int);
    tr.run("push/pop string",     test_push_pop_string);

    std::cout << "\n[ Empty cases ]\n";
    tr.run("empty pop",           test_empty_pop);
    tr.run("empty peek",          test_empty_peek);

    std::cout << "\n[ Rule of Five ]\n";
    tr.run("move constructor",    test_move_constructor);
    tr.run("move assignment",     test_move_assignment);
    tr.run("copy constructor",    test_copy_constructor);
    tr.run("copy assignment",     test_copy_assignment);

    std::cout << "\n[ Find ]\n";
    tr.run("find empty",          test_find_empty);
    tr.run("find not found",      test_find_not_found);
    tr.run("find one",            test_find_one);
    tr.run("find all",            test_find_all);

    std::cout << "\n[ Other ]\n";
    tr.run("initial capacity",    test_initial_capacity);
    tr.run("len after ops",       test_len_after_operations);

    tr.summary();
    return tr.exit_code();
}
