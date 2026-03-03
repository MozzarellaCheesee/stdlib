#pragma once
#include "stack.h"
#include "vector.h"
#include <iostream>

namespace stdlib {

    template<typename T>
    Stack<T>::Stack(const int initial_capacity) {
        if (initial_capacity < 8) throw std::invalid_argument("Initial capacity must be greater than 8.");
        Vector<T> vec;
        data_ = vec;
    }

    template <typename T>
    Stack<T>::Stack(const Stack& copy) noexcept{
        data_ = copy.data_;
    }

    template <typename T>
    Stack<T>& Stack<T>::operator=(const Stack& copy) noexcept {
        if (this == &copy) return *this;
        Vector<T> new_data(copy.data_);
        data_ = new_data;
        return *this;
    }

    template <typename T>
    Stack<T>::Stack(Stack&& moved) noexcept {
        data_ = moved.data_;
        moved.data_.~T();
    }

    template <typename T>
    Stack<T>& Stack<T>::operator=(Stack&& moved) noexcept {
        if (this == moved) return *this;
        data_ = moved.data_;
        moved.data_.~T();
        return *this;
    }

    template <typename T>
    void Stack<T>::push(const T& value) {
        data_.push_back(value);
    }

    template <typename T>
    T Stack<T>::pop() {
        data_.pop_back();
    }

    template <typename T>
    const T& Stack<T>::peek() const {
        return data_[data_.size() - 1];
    }

    template <typename T>
    bool Stack<T>::isEmpty() const {
        return data_.size() == 0;
    }

    template <typename T>
    void Stack<T>::print() {
        if (isEmpty()) {
            std::cout << "Stack is empty\n";
            return;
        }
        size_t i = data_.size()-1;
        for (auto el : data_) {
            std::cout << i << ": " << el << "\n";
            --i;
        }
    }

    template <typename T>
    Vector<T> Stack<T>::find(const T& value) const {
        if (isEmpty()) return {nullptr, 0};

        size_t count = 0;
        for (auto el : data_) {
            if (el == value) count++;
        }

        Vector<T> result(count, 0);

        for (size_t i = 0, x = 0; i < data_.size(); i++) {
            if(data_[i] == value) {
                result[x] = i;
                x++;
            }
        }   
    }

}




