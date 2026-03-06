#pragma once
#include "vector.h"

namespace stdlib {
    typedef bool success;

    template <typename T>
    class Stack {
    private:
        Vector<T>   data_;                                              // Вектор данных стека
    public:
        explicit    Stack(const std::size_t initial_capacity = 8);      // Стандартный конструктор 
        ~Stack() = default;                                             // Деструктор
        Stack(Stack&&)                          noexcept;               // Конструктор перемещения
        Stack(const Stack&);                                            // Конструктор копирования
        Stack&      operator=(Stack&&)          noexcept;               // Синтематика перемещения
        Stack&      operator=(const Stack&);                            // Синтематика копирования
        void        push(const T&);                                     // Отправить элемент в верх стека
        T           pop();                                              // Удалить и вернуть верхний элемент стека
        void        print();                                            // Вывести элементы стека
        size_t      len()                       const;                  // Получить размер стека
        const T&    peek()                      const;                  // Вернуть верхний элемент стека без удаления
        bool        empty()                     const;                  // Проверка на пустоту
        Vector<std::size_t>   find(const T&)    const;                  // Возвращает индексы позиций искомого элемента
    };

}

#include "../stdlib/detail/stack.tpp"