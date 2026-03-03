#include "../stdlib/vector.h"
#include "../stdlib/stack.h"
#include <iostream>

int main() {
    mystd::Vector<int> vec{1, 3, 5, 3};
    for (auto el : vec) {
        std::cout << el << " ";
    }

    mystd::Stack<int> stack;
    stack.push(4);
    stack.push(8);
    stack.push(76);
    stack.push(4);
    stack.push(4);
    std::cout << "\n";
    stack.print();
}