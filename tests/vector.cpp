#include "../stdlib/vector.h"
#include <iostream>

int main() {
    mystd::Vector<int> vec{1, 3, 5, 3};
    for (auto el : vec) {
        std::cout << el << " ";
    }
}