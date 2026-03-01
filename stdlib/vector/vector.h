#pragma once
#include <iostream>

template <typename T>
class MyVector {
public:
    // ─── Конструкторы ───────────────────────────────────────────
    MyVector();                                             	// Конструктор по умолчанию
    MyVector(std::initializer_list<T> list);                  	// Конструктор из списка инициализации {1,2,3}
    template<typename InputIt>                              	// Шаблонизированный
    MyVector(InputIt first, InputIt last);                    	// Конструктор из диапазона итераторов
    explicit    MyVector(std::size_t n, const T& val = T{});  	// Конструктор из n элементов со значением val

    // ─── Rule of Five ───────────────────────────────────────────
    ~MyVector();                                            	// Деструктор
    MyVector(MyVector&&);                                   	// Конструктор перемещения
    MyVector(const MyVector&);                              	// Конструктор копирования
    MyVector&   operator=(MyVector&&);                      	// Перегрузка оператора перемещения
    MyVector&   operator=(const MyVector&);                 	// Перегрузка оператора копирования

    // ─── Доступ к элементам ─────────────────────────────────────
    T&          operator[](std::size_t i);                  	// Доступ по индексу без проверки границ
    T&          at(std::size_t i);                       		// Доступ по индексу с проверкой границ
    T&          front();                                		// Первый элемент вектора
    T&          back();                                  		// Последний элемент вектора
    T*          data();                                 		// Сырой указатель на буфер

    const T&    operator[](std::size_t i) const;          		// Доступ по индексу без проверки границ const
    const T&    at(std::size_t i)         const;         		// Доступ по индексу с проверкой границ const
    const T&    front()                   const;          		// Первый элемент вектора const
    const T&    back()                    const;          		// Последний элемент вектора const
    const T*    data()                    const;          		// Сырой указатель на буфер const

    // ─── Размер и ёмкость ───────────────────────────────────────
    std::size_t size()     const noexcept; 						// Число элементов
    std::size_t capacity() const noexcept; 						// Выделенная ёмкость
    bool        empty()    const noexcept; 						// Проверка пустоты size_ == 0
    void        reserve(std::size_t n);                   	    // Выделить память без изменения size_
    void        shrink_to_fit();                            	// Уменьшить capacity_ до size_

    // ─── Модификация ────────────────────────────────────────────
    void push_back(const T& val);                   			// Копирующая вставка в конец
    void push_back(T&& val);                        			// Перемещающая вставка в конец
    void pop_back();                                			// Удалить последний элемент
    void resize(std::size_t n, const T& val = T{}); 			// Изменить size_, добавляя val или удаляя
    void swap(MyVector&) noexcept;                  			// Поменять местами содержимое векторов
    void clear() 	     noexcept;                          	// Вызвать деструкторы, обнулить size_

    // ─── Итераторы ──────────────────────────────────────────────
    T*                            	begin()	    noexcept;       // Итератор на начало
    T*                              end() 		noexcept;       // Итератор на конец
    std::reverse_iterator<T*>       rbegin()    noexcept;       // обратный итератор на конец
    std::reverse_iterator<T*>       rend()      noexcept;       // обратный итератор на начало

    const T&                       	begin()     const noexcept; // Итератор на начало неявно const
    const T&                        end()    	const noexcept; // Итератор на конец неявно const
    const T*                        cbegin() 	const noexcept; // Итератор на начало явно const
    const T*                        cend()  	const noexcept; // Итератор на конец явно const
    std::reverse_iterator<const T*> rbegin()    const noexcept; // обратный итератор на конец const
    std::reverse_iterator<const T*> rend()      const noexcept; // обратный итератор на начало const

private:
    T*          data_     = nullptr;                            // Указатель на массив данных
    std::size_t size_     = 0;                                  // Количество данных в массиве
    std::size_t capacity_ = 0;                              	// Выделенный размер массива под данные
    void        reallocate(std::size_t newCapacity);        	// Приватная функция увелечения размера массива для данных
};


#include "detail/vector.tpp"