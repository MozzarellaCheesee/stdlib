#pragma once
#include "../stack.h"
#include "../vector.h"
#include <iostream>

namespace stdlib {

    template <typename T>
    Stack<T>::Stack(const size_t initial_capacity) : data_() {
        data_.reserve(initial_capacity);
    }

    template <typename T>
    Stack<T>::Stack(const Stack& copy) : data_(copy.data_) {}

    template <typename T>
    Stack<T>& Stack<T>::operator=(const Stack& copy) {
        if (this == &copy) return *this;
        data_ = copy.data_;
        return *this;
    }

    template <typename T>
    Stack<T>::Stack(Stack&& moved) noexcept : data_(std::move(moved.data_)) {}

    template <typename T>
    Stack<T>& Stack<T>::operator=(Stack&& moved) noexcept {
        if (this == &moved) return *this;
        data_ = std::move(moved.data_);
        return *this;
    }

    template <typename T>
    void Stack<T>::push(const T& value) {
        data_.push_back(value);
    }

    template <typename T>
    T Stack<T>::pop() {
        if (empty()) throw std::runtime_error("stack.pop(): empty stack");
        T value = std::move(data_[data_.size() - 1]);
        data_.pop_back();
        return value;
    }

    template <typename T>
    const T& Stack<T>::peek() const {
        if (empty()) throw std::runtime_error("stack.peek(): empty stack");
        return data_[data_.size() - 1];
    }

    template <typename T>
    bool Stack<T>::empty() const {
        return data_.size() == 0;
    }

    template <typename T>
    void Stack<T>::print() {
        if (empty()) {
            std::cout << "Stack is empty\n";
            return;
        }
        for (size_t i = data_.size(); i-- > 0;) {
            std::cout << i << ": " << data_[i] << "\n";
        }
    }

    template <typename T>
    size_t Stack<T>::len() const {
        return data_.size();
    }

    template <typename T>
    Vector<std::size_t> Stack<T>::find(const T& value) const {
        Vector<std::size_t> result;
        for (size_t i = 0; i < data_.size(); i++) {
            if (data_[i] == value) result.push_back(i);
        }
        return result;
    }
}




