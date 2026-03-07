#pragma once
#include <cstddef>
#include <initializer_list>
#include <iterator>

namespace stdlib {
    template<typename T>
    class List {
    private:
        struct BaseNode {
            BaseNode* prev_;
            BaseNode* next_;
        };
        struct Node : BaseNode {
            T         data_;
            template<typename... Args>
            Node(Args&&... args) : data_(std::forward<Args>(args)...) {}
        };
        BaseNode    sentinel_;
        std::size_t size_;        
        template<typename... Args>
        Node* make_node(Args&&... args);
        void insert_before(BaseNode*, Node*);
    public:
        struct Iterator {
            private:
                BaseNode* current_ = nullptr;
                friend class List<T>;
            public:
                using iterator_category = std::bidirectional_iterator_tag;
                using value_type        = T;
                using difference_type   = std::ptrdiff_t;
                using pointer           = T*;
                using reference         = T&;

                Iterator() = default;
                Iterator(BaseNode* node) : current_(node) {}

                T& operator*()  const { return static_cast<Node*>(current_)->data_; }
                T* operator->() const { return &static_cast<Node*>(current_)->data_; }

                Iterator& operator++() { current_ = current_->next_; return *this; }
                Iterator  operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
                Iterator& operator--() { current_ = current_->prev_; return *this; }
                Iterator  operator--(int) { Iterator tmp = *this; --(*this); return tmp; }

                bool operator==(const Iterator& o) const { return current_ == o.current_; }
                bool operator!=(const Iterator& o) const { return current_ != o.current_; }
        };
        struct ConstIterator {
            private:
                const BaseNode* current_ = nullptr;
                friend class List<T>;
            public:
                using iterator_category = std::bidirectional_iterator_tag;
                using value_type        = T;
                using difference_type   = std::ptrdiff_t;
                using pointer           = const T*;
                using reference         = const T&;

                ConstIterator() = default;
                ConstIterator(const BaseNode* node) : current_(node) {}
                ConstIterator(const Iterator& it) : current_(it.current_) {}                        

                const T& operator*()  const { return static_cast<const Node*>(current_)->data_; }
                const T* operator->() const { return &static_cast<const Node*>(current_)->data_; }

                ConstIterator& operator++() { current_ = current_->next_; return *this; }
                ConstIterator  operator++(int) { ConstIterator tmp = *this; ++(*this); return tmp; }
                ConstIterator& operator--() { current_ = current_->prev_; return *this; }
                ConstIterator  operator--(int) { ConstIterator tmp = *this; --(*this); return tmp; }

                bool operator==(const ConstIterator& o) const { return current_ == o.current_; }
                bool operator!=(const ConstIterator& o) const { return current_ != o.current_; }
        };
        using ReverseIterator = std::reverse_iterator<Iterator>;
        using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
        
        // ─── Конструкторы ───────────────────────────────────────────
        List()                          noexcept;                                                   // Базовый конструктор
        List(std::initializer_list<T>);                                                             // Конструктор из списка инициализации {1,2,3}
        template<std::input_iterator InputIt>                                                       // Шаблонизированный
        List(InputIt, InputIt);                                                                     // Конструктор из диапазона итераторов
        explicit List(std::size_t, const T& val = T{});                                             // Конструктор из n элементов со значением val
        
        // ─── Rule of Five ───────────────────────────────────────────
        ~List()                         noexcept;                                                   // Деструктор
        List(List&&)                    noexcept;                                                   // Конструктор перемещения
        List(const List&);                                                                          // Конструктор копирования
        List& operator=(List&&)         noexcept;                                                   // Оператор перемещающего присваивания
        List& operator=(const List&);                                                               // Оператор копирующего присваивания
        
        // ─── Модификация ────────────────────────────────────────────
        void push_front(const T&);                                                                  // Копирование в начало списка
        void push_back(const T&);                                                                   // Копирование в конец списка
        Iterator  insert(Iterator, const T&);                                                       // Копирование в список
        void push_front(T&&);                                                                       // Перемещение в начало списка
        void push_back(T&&);                                                                        // Перемещение в конец списка
        Iterator  insert(Iterator, T&&);                                                            // Перемещение в список
        
        void pop_front();                                                                           // Удалить первый элемент списка
        void pop_back();                                                                            // Удалить последний элемент списка 
        Iterator erase(Iterator);                                                                   // Удалить элемент из списка
        void remove(const T&) requires std::equality_comparable<T>;                                 // Удалить все элемены из списка по значению
        
        // ─── Доступ к элементам ─────────────────────────────────────
        T&                   operator[](std::size_t);                                               // Оператор доступа по индексу без проверки O(n)
        const T&             operator[](std::size_t) const;                                         // Оператор доступа по индексу без проверки O(n) const
        T&                   at(std::size_t);                                                       // Оператор доступа по индексу с проверкой O(n)
        const T&             at(std::size_t)         const;                                         // Оператор доступа по индексу с проверкой O(n) const
        T&                   front();                                                               // Получить ссылку на превый элемент в списке
        T&                   back();                                                                // Получить ссылку на последний элемент в списке
        const T&             front()    const;                                                      // Получить ссылку на превый элемент в списке const
        const T&             back()     const;                                                      // Получить ссылку на последний элемент в списке const
        Iterator             begin()    noexcept        { return Iterator(sentinel_.next_); }       // Получить итератор на первый элемент в списке
        Iterator             end()      noexcept        { return Iterator(&sentinel_); }            // Получить итератор на последний элемент в списке
        ConstIterator        begin()    const noexcept  { return ConstIterator(sentinel_.next_); }  // Получить итератор на первый элемент не явно const
        ConstIterator        end()      const noexcept  { return ConstIterator(&sentinel_); }       // Получить итератор на последний элемент не явно const
        ConstIterator        cbegin()   const noexcept  { return ConstIterator(sentinel_.next_); }  // Получить итератор на первый элемент явно const
        ConstIterator        cend()     const noexcept  { return ConstIterator(&sentinel_); }       // Получить итератор на последний элемент явно const
        ReverseIterator      rbegin()   noexcept        { return ReverseIterator(end()); }          // Получить обратный итератор на первый элемент
        ReverseIterator      rend()     noexcept        { return ReverseIterator(begin()); }        // Получить обратный итератор на последний элемент
        ConstReverseIterator rbegin()   const noexcept  { return ConstReverseIterator(end()); }     // Получить обратный итератор на последний элемент не явно const
        ConstReverseIterator rend()     const noexcept  { return ConstReverseIterator(begin()); }   // Получить обратный итератор на первый элемент не явно const
        ConstReverseIterator crbegin()  const noexcept  { return ConstReverseIterator(end()); }     // Получить обратный на последний элемент явно const
        ConstReverseIterator crend()    const noexcept  { return ConstReverseIterator(begin()); }   // Получить обратный на последний элемент явно const
        
        // ─── Размер и ёмкость ───────────────────────────────────────
        std::size_t size()      const noexcept {return size_; }                                     // Получить размер списка
        bool        empty()     const noexcept { return size_ == 0; }                               // Проверить пустоту списка
        
        // ─── Утилиты ────────────────────────────────────────────────
        void        clear()     noexcept;                                                           // Очистить все элементы списка
        void        swap(List&) noexcept;                                                           // Поменять местами с элементом
        bool        operator==(const List&) const requires std::equality_comparable<T>;             // Перегрузка оператора сравнения
    };  

    template<typename T>
    bool operator==(const List<T>& a, const List<T>& b) {
        return a.operator==(b);
    }

    template<typename T>
    bool operator!=(const List<T>& a, const List<T>& b) {
        return !(a == b);
    }

    template<typename T>
    bool operator<(const List<T>& a, const List<T>& b) {
        return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
    }

    template<typename T>
    bool operator<=(const List<T>& a, const List<T>& b) {
        return !(b < a);
    }

    template<typename T>
    bool operator>(const List<T>& a, const List<T>& b) {
        return b < a;
    }

    template<typename T>
    bool operator>=(const List<T>& a, const List<T>& b) {
        return !(a < b);
    }

    template<typename T>
    void swap(List<T>& a, List<T>& b) noexcept {
        a.swap(b);
    }
}

#include "../stdlib/detail/list.tpp"
