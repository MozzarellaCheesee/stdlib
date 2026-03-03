#pragma once
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <memory>


namespace stdlib {
    template<typename T>
    class Vector {
    public:
        // ─── Конструкторы ───────────────────────────────────────────
        Vector() noexcept;                                          // Конструктор по умолчанию
        Vector(std::initializer_list<T>);                  	        // Конструктор из списка инициализации {1,2,3}
        template<typename InputIt>                              	// Шаблонизированный
        Vector(InputIt, InputIt);                               	// Конструктор из диапазона итераторов
        explicit    Vector(std::size_t, const T& val = T{});  	    // Конструктор из n элементов со значением val

        // ─── Rule of Five ───────────────────────────────────────────
        ~Vector() = default;                                        // Деструктор
        Vector(Vector&&) noexcept;                                  // Конструктор перемещения
        Vector(const Vector&);                                      // Конструктор копирования
        Vector&   operator=(Vector&&) noexcept;                     // Перегрузка оператора перемещения
        Vector&   operator=(const Vector&) noexcept;                // Перегрузка оператора копирования

        // ─── Доступ к элементам ─────────────────────────────────────
        T&          operator[](std::size_t);                    	// Доступ по индексу без проверки границ
        T&          at(std::size_t);                         		// Доступ по индексу с проверкой границ
        T&          front();                                		// Первый элемент вектора
        T&          back();                                  		// Последний элемент вектора
        T*          data();                                 		// Сырой указатель на буфер

        const T&    operator[](std::size_t)         const;          // Доступ по индексу без проверки границ const
        const T&    at(std::size_t)                 const;        	// Доступ по индексу с проверкой границ const
        const T&    front()                         const;    		// Первый элемент вектора const
        const T&    back()                          const;          // Последний элемент вектора const
        const T*    data()                          const;          // Сырой указатель на буфер const

        // ─── Размер и ёмкость ───────────────────────────────────────
        std::size_t size()                          const noexcept; // Число элементов
        std::size_t capacity()                      const noexcept; // Выделенная ёмкость
        bool        empty()                         const noexcept; // Проверка пустоты size_ == 0
        void        reserve(std::size_t);                   	    // Выделить память без изменения size_
        void        shrink_to_fit();                                // Уменьшить capacity_ до size_

        // ─── Модификация ────────────────────────────────────────────
        void        resize(std::size_t, const T& val = T{}); 	    // Изменить size_, добавляя val или удаляя
        void        push_back(const T&);                   		    // Копирующая вставка в конец
        void        push_back(T&&);                        		    // Перемещающая вставка в конец
        void        pop_back();                                     // Удалить последний элемент
        void        swap(Vector&)                   noexcept;       // Поменять местами содержимое векторов
        void        clear() 	                    noexcept;       // Вызвать деструкторы, обнулить size_

        // ─── Итераторы ──────────────────────────────────────────────
        T*                            	begin()	    noexcept;       // Итератор на начало
        T*                              end() 		noexcept;       // Итератор на конец
        std::reverse_iterator<T*>       rbegin()    noexcept;       // обратный итератор на конец
        std::reverse_iterator<T*>       rend()      noexcept;       // обратный итератор на начало

        const T*                       	begin()     const noexcept; // Итератор на начало неявно const
        const T*                        end()    	const noexcept; // Итератор на конец неявно const
        const T*                        cbegin() 	const noexcept; // Итератор на начало явно const
        const T*                        cend()  	const noexcept; // Итератор на конец явно const
        std::reverse_iterator<const T*> rbegin()    const noexcept; // обратный итератор на конец const
        std::reverse_iterator<const T*> rend()      const noexcept; // обратный итератор на начало const

    private:
        std::size_t          size_     = 0;                         // Количество данных в массиве
        std::size_t          capacity_ = 0;                         // Выделенный размер массива под данные
        std::unique_ptr<T[]> data_;                                 // Указатель на массив данных
        void                 reallocate(std::size_t);        	    // Приватная функция увелечения размера массива для данных
        std::size_t          max_size()             const noexcept; // Максимальное количество элементов которое может быть в векторе
    };
    
    // ─── Операторы сравенения ───────────────────────────────────────
    template<typename T>
    bool operator==(const Vector<T>& a, const Vector<T>& b);

    template<typename T>
    bool operator!=(const Vector<T>& a, const Vector<T>& b);

    template<typename T>
    bool operator<(const Vector<T>& a, const Vector<T>& b);

    template<typename T>
    bool operator<=(const Vector<T>& a, const Vector<T>& b);

    template<typename T>
    bool operator>(const Vector<T>& a, const Vector<T>& b);

    template<typename T>
    bool operator>=(const Vector<T>& a, const Vector<T>& b);

    // ─── Свободная функция swap ─────────────────────────────────────

    template<typename T>
    void swap(Vector<T>& a, Vector<T>& b) noexcept;           // для совместимости с std::swap
}

#include "../stdlib/vector.tpp"