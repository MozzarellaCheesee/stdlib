#pragma once
#include "../list.h"
#include <initializer_list>

namespace mtdlib {

    template<typename T>
    template<typename... Args>
    List<T>::Node* List<T>::make_node(Args&&... args) { return new Node(std::forward<Args>(args)...); }

    template<typename T>
    void List<T>::insert_before(BaseNode* pos, Node* node) {
            node->prev_ = pos->prev_;
            node->next_ = pos;
            pos->prev_->next_ = node;
            pos->prev_ = node;
            ++size_;
        }

    // ─── Конструкторы ───────────────────────────────────────────
    template<typename T>
    List<T>::List() noexcept : size_(0), sentinel_{&sentinel_, &sentinel_} {}
    
    template<typename T>
    List<T>::List(std::initializer_list<T> il) : List(il.begin(), il.end()) {}

    template<typename T>
    template<std::input_iterator InputIt>
    List<T>::List(InputIt first, InputIt last) {
        for (; first != last; ++first)
            push_back(*first);
    }

    template<typename T>
    List<T>::List(std::size_t len, const T& val) : List() {
        for (std::size_t i = 0; i < len; i++)
            push_back(val);
    }

    // ─── Rule of Five ───────────────────────────────────────────
    template<typename T>
    List<T>::~List() noexcept {
        clear();
    }

    template<typename T>
    List<T>::List(List&& other) noexcept {
        if (!other.empty()) {
            sentinel_.next_ = other.sentinel_.next_;
            sentinel_.prev_ = other.sentinel_.prev_;

            sentinel_.next_->prev_ = &sentinel_;
            sentinel_.prev_->next_ = &sentinel_;

            size_ = other.size();
            other.sentinel_.next_ = &other.sentinel_;
            other.sentinel_.prev_ = &other.sentinel_;
            other.size_ = 0;
        }
    }

    template<typename T>
    List<T>::List(const List& other) : List(other.begin(), other.end()) {}

    template<typename T>
    List<T>& List<T>::operator=(List&& other) noexcept {
        if (this == &other) return *this;
        clear();
        if (!other.empty()) {
            sentinel_.next_ = other.sentinel_.next_;
            sentinel_.prev_ = other.sentinel_.prev_;

            sentinel_.next_->prev_ = &sentinel_;
            sentinel_.prev_->next_ = &sentinel_;

            size_ = other.size();
            other.sentinel_.next_ = &other.sentinel_;
            other.sentinel_.prev_ = &other.sentinel_;
            other.size_ = 0;
        }
    }

    template<typename T>
    List<T>& List<T>::operator=(const List& other) {
        if (this == &other) return *this;
        List tmp(other);
        swap(tmp);
        return *this;
    }

    // ─── Модификация ────────────────────────────────────────────
    template<typename T>
    void List<T>::push_front(const T& val) {
        insert_before(sentinel_.next_, make_node(val));
    }

    template<typename T>
    void List<T>::push_back(const T& val) {
        insert_before(&sentinel_, make_node(val));
    }

    template<typename T>
    typename List<T>::Iterator List<T>::insert(Iterator it, const T& val) {
        Node* node = make_node(val);
        insert_before(it.current_, node);
        return Iterator(node);
    }

    template<typename T>
    void List<T>::push_front(T&& val) {
        insert_before(sentinel_.next_, make_node(std::move(val)));
    }

    template<typename T>
    void List<T>::push_back(T&& val) {
        insert_before(&sentinel_, make_node(std::move(val)));
    }

    template<typename T>
    typename List<T>::Iterator List<T>::insert(Iterator it, T&& val) {
        Node* node = make_node(std::move(val));
        insert_before(it.current_, node);
        return Iterator(node);
    }

    template<typename T>
    void List<T>::pop_front() {
        erase(begin());
    }

    template<typename T>
    void List<T>::pop_back() {
        erase(--end());
    }

    template<typename T>
    typename List<T>::Iterator List<T>::erase(Iterator it) {
        Node* node = static_cast<Node*>(it.current_);
        BaseNode* next = node->next_;
        
        node->prev_->next_ = node->next_;
        node->next_->prev_ = node->prev_;
        
        delete node;
        --size_;
        
        return Iterator(next);
    }

    template<typename T>
    void List<T>::remove(const T& val) requires std::equality_comparable<T> {
        Iterator it = begin();
        while (it != end()) {
            if (*it == val)
                it = erase(it);
            else
                ++it;
        }
    }

    // ─── Утилиты ────────────────────────────────────────────────

    template<typename T>
    void List<T>::clear() noexcept
    {
        BaseNode* current = sentinel_.next_;
        while (current != &sentinel_) {
            BaseNode* next = current->next_;
            delete static_cast<Node*>(current);
            current = next;
        }
        sentinel_.prev_ = &sentinel_;
        sentinel_.next_ = &sentinel_;
        size_ = 0;
    }

    template<typename T>
    void List<T>::swap(List& other) noexcept {
        if (this == &other) return;

        std::swap(sentinel_.next_, other.sentinel_.next_);
        std::swap(sentinel_.prev_, other.sentinel_.prev_);

        sentinel_.next_->prev_ = &sentinel_;
        sentinel_.prev_->next_ = &sentinel_;

        other.sentinel_.next_->prev_ = &other.sentinel_;
        other.sentinel_.prev_->next_ = &other.sentinel_;

        std::swap(size_, other.size_);
    }

    template<typename T>
    bool List<T>::operator==(const List& other) const requires std::equality_comparable<T> {
        if (size() != other.size()) return false;
        auto it_a = begin(), it_b = other.begin();
        while (it_a != end()) {
            if (!(*it_a == *it_b)) return false;
            ++it_a; ++it_b;
        }
        return true;
    }
    
}