#pragma once
#include "vector.h"

namespace stdlib {
    typedef bool success;

    template <typename T = int>
    class Stack {
    private:
        Vector<T> data_;                                // Вектор данных стека
    public:
        explicit    Stack(int initial_capacity = 16);   // Стандартный конструктор 
        ~Stack() = default;                             // Деструктор
        Stack(const Stack&)                 noexcept;   // Конструктор копирования
        Stack(Stack&&)                      noexcept;   // Конструктор перемещения
        Stack&      operator=(Stack&&)      noexcept;   // Синтематика перемещения
        Stack&      operator=(const Stack&) noexcept;   // Синтематика копирования
        void        push(const T&);                     // Отправить элемент в верх стека
        T           pop();                              // Удалить и вернуть верхний элемент стека
        void        print();                            // Вывести элементы стека
        size_t      len()                   const;      // Получить размер стека
        const T&    peek()                  const;      // Вернуть верхний элемент стека без удаления
        bool        isEmpty()               const;      // Проверка на пустоту
        Vector<T>   find(const T&)          const;      // Возвращает индексы позиций искомого элемента
    };

}

#include "../stdlib/stack.tpp"