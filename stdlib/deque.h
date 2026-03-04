#include "vector.h"

namespace stdlib {
    template<typename T>
    class Deque {
    private:
        Vector<T> buf;
        size_t    head = 0;   // индекс первого элемента
        size_t    tail = 0;   // индекс следующей свободной позиции
        size_t    size = 0;

    public:
        
    };
}



#include "../stdlib/detail/deque.tpp"