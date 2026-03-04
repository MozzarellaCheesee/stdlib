#include "../stdlib/vector.h"
#include "../stdlib/stack.h"
#include <iostream>

int main() {
    stdlib::Vector<int> vec;
    for (std::size_t i = 3; i < 65537; i++) {
        vec.push_back(i);
    }
    std::cout << vec.capacity() << " " << vec.size() << "\n";

    stdlib::Stack<int> stack;
    stack.push(4);
    stack.push(8);
    stack.push(76);
    stack.push(4);
    stack.push(4);
    std::cout << "\n";
    stack.print();
}