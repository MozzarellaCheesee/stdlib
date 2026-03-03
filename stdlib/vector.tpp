#pragma once
#include "vector.h"
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <limits>

namespace stdlib {

    template<typename T>
    Vector<T>::Vector() noexcept : size_(0), capacity_(0) {}

    // ─── Конструкторы ───────────────────────────────────────────
    template<typename T>
    Vector<T>::Vector(std::initializer_list<T> list) 
        : size_(list.size()), capacity_(size_) {
        data_ = std::make_unique<T[]>(capacity_);
        std::copy(list.begin(), list.end(), data_.get());
    }

    template<typename T>
    template<typename InputIt>
    Vector<T>::Vector(InputIt first, InputIt last) {
        size_ = static_cast<size_t>(std::distance(first, last));
        if (size_ == 0) return;
        capacity_ = size_;
        data_ = std::make_unique<T[]>(capacity_);
        std::copy(first, last, data_.get());
    }

    template<typename T>
    Vector<T>::Vector(size_t n, const T& val) 
        : size_(n), capacity_(n) {
        data_ = std::make_unique<T[]>(capacity_);
        std::fill(data_.get(), data_.get() + size_, val);
    }


    // ─── Rule of Five ───────────────────────────────────────────
    template<typename T>
    Vector<T>::Vector(Vector&& other) noexcept 
        : size_(other.size_)
        , capacity_(other.capacity_)
        , data_(std::move(other.data_)) {
        other.size_ = 0;
        other.capacity_ = 0;
    }

    template<typename T>
    Vector<T>::Vector(const Vector& other)
        : size_(other.size_), capacity_(other.capacity_) {
        data_ = std::make_unique<T[]>(capacity_);
        std::copy(other.data_.get(), other.data_.get() + other.size_, data_.get());
    }

    template<typename T>
    Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
        if (this == &other) return *this;

        data_.reset();
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = std::move(other.data_);

        other.size_ = 0;
        other.capacity_ = 0;
    }

    template<typename T>
    Vector<T>& Vector<T>::operator=(const Vector& other) noexcept {
        if (this == &other) return *this;

        if (other.size_ <= capacity_) {
            std::copy(other.data_.get(), other.data_.get() + other.size_, data_.get());
            size_ = other.size_;
            return *this;
        }

        std::unique_ptr<T[]> temp(new T[other.size_]);
        std::copy(other.data_.get(), other.data_.get() + other.size_, temp.get());

        data_ = std::move(temp);
        size_ = other.size_;
        return *this;
    }

    // ─── Доступ к элементам ─────────────────────────────────────
    template<typename T>
    T& Vector<T>::operator[](std::size_t i) {
        return data_[i];
    }

    template<typename T>
    T& Vector<T>::at(std::size_t i) {
        if (empty()) throw std::out_of_range("Vector::back: empty vector");
        if (i >= size_) throw std::out_of_range("Vector::at: index " + std::to_string(i) + " >= size " + std::to_string(size_));
        return data_[i];
    }

    template<typename T>
    T& Vector<T>::front() {
        if (empty()) throw std::out_of_range("Vector::back: empty vector");
        return data_[0];
    }

    template<typename T>
    T& Vector<T>::back() {
        if (empty()) throw std::out_of_range("Vector::back: empty vector");
        return data_[size_ - 1];
    }

    template<typename T>
    T* Vector<T>::data() {
        return data_.get();
    }

    template<typename T>
    const T& Vector<T>::operator[](std::size_t i) const {
        return data_[i];
    }

    template<typename T>
    const T& Vector<T>::at(std::size_t i) const {
        if (empty()) throw std::out_of_range("Vector::back: empty vector");
        if (i >= size_) throw std::out_of_range("Vector::at: index " + std::to_string(i) + " >= size " + std::to_string(size_));
        return data_[i];
    }

    template<typename T>
    const T& Vector<T>::front() const {
        if (empty()) throw std::out_of_range("Vector::back: empty vector");
        return data_[0];
    }

    template<typename T>
    const T& Vector<T>::back() const {
        if (empty()) throw std::out_of_range("Vector::back: empty vector");
        return data_[size_ - 1];
    }

    template<typename T>
    const T* Vector<T>::data() const {
        return data_.get();
    }

    // ─── Размер и ёмкость ───────────────────────────────────────
    template<typename T>
    std::size_t Vector<T>::size() const noexcept {
        return size_;
    }

    template<typename T>
    std::size_t Vector<T>::capacity() const noexcept {
        return capacity_;
    }

    template<typename T>
    bool Vector<T>::empty() const noexcept {
        return size_ == 0u;
    }

    template<typename T>
    void Vector<T>::reserve(std::size_t new_capacity) {
        if (new_capacity <= capacity_) return;
        reallocate(new_capacity);
    }

    template<typename T>
    void Vector<T>::shrink_to_fit() {
        if (capacity_ == size_) return;

        Vector tmp(*this);
        tmp.capacity_ = tmp.size_;
        swap(tmp);
    }

    // ─── Модификация ────────────────────────────────────────────

    template<typename T>
    void Vector<T>::resize(std::size_t new_size, const T& val) {
        if (new_size < size_) {
            for (std::size_t i = new_size; i < size_; ++i) {
                data_[i].~T();
            }
            size_ = new_size;
            return;
        }

        if (new_size > size_) {
            if (new_size > capacity_) reallocate(new_size);

            for (std::size_t i = new_size; i < size_; ++i) {
                new (&data_[i]) T(val);
            }
            size_ = new_size;
        }
    }

    template<typename T>
    void Vector<T>::push_back(const T& value) {
        if (size_ == capacity_) {
            size_t new_cap = capacity_ == 0 ? 1 : capacity_ * 3 / 2;
            reallocate(new_cap);
        }
        new (data_.get() + size_) T(value);  // Placement new
        ++size_;
    }

    template<typename T>
    void Vector<T>::push_back(T&& value) {
        if (size_ == capacity_) {
            std::size_t new_capacity = capacity_ == 0 ? 1 : static_cast<std::size_t>(capacity_ * 1.5);
            reallocate(new_capacity);
        }
        
        new (&data_[size_]) T(std::forward<T>(value));
        ++size_;
    }

    template<typename T>
    void Vector<T>::pop_back()  {
        if (empty()) return;
        data_[--size_].~T();
    }

    template<typename T>
    void Vector<T>::swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    template<typename T>
    void Vector<T>::clear() noexcept {
        for (std::size_t i = size_; i > 0; ) data_[--i].~T();
        size_ = 0;
    }

    // ─── Итераторы ──────────────────────────────────────────────

    template<typename T>
    T* Vector<T>::begin() noexcept {
        return data_.get();
    }

    template<typename T>
    T* Vector<T>::end() noexcept {
        return data_.get() + size_;
    }

    template<typename T>
    std::reverse_iterator<T*> Vector<T>::rbegin() noexcept {
        return std::reverse_iterator<T*>(end());
    }

    template<typename T>
    std::reverse_iterator<T*> Vector<T>::rend() noexcept {
        return std::reverse_iterator<T*>(begin()); 
    }

    template<typename T>
    const T* Vector<T>::begin() const noexcept {
        return data_.get();
    }

    template<typename T>
    const T* Vector<T>::end() const noexcept {
        return data_.get() + size_;
    }

    template<typename T>
    const T* Vector<T>::cbegin() const noexcept {
        return data_.get();
    }

    template<typename T>
    const T* Vector<T>::cend() const noexcept {
        return data_.get() + size_;
    }

    template<typename T>
    std::reverse_iterator<const T*> Vector<T>::rbegin() const noexcept {
        return std::reverse_iterator<const T*>(end());
    }

    template<typename T>
    std::reverse_iterator<const T*> Vector<T>::rend() const noexcept {
        return std::reverse_iterator<const T*>(begin());
    }

    // ─── Приватные функции ──────────────────────────────────────

    template<typename T>
    void Vector<T>::reallocate(std::size_t new_capacity) {
        if (new_capacity > max_size()) throw std::length_error("Vector::reserve: new_cap > max_size()");
        std::unique_ptr<T[]> temp(new T[new_capacity]);
        std::move(data_.get(), data_.get() + size_, temp.get());
        data_ = std::move(temp);
        capacity_ = new_capacity;
    }

    template<typename T>
    std::size_t Vector<T>::max_size() const noexcept {
        return std::numeric_limits<std::size_t>::max() / sizeof(T);
    }

    // ─── Свободная функция swap ─────────────────────────────────

    template<typename T>
    void swap(Vector<T>& a, Vector<T>& b) noexcept {
        using std::swap;
        swap(a.data_, b.data_);
        swap(a.size_, b.size_);
        swap(a.capacity_, b.capacity_);
    }

    template<typename T>
    bool operator==(const Vector<T>& a, const Vector<T>& b) {
        return a.size() == b.size() && 
            std::equal(a.begin(), a.end(), b.begin());
    }

    template<typename T>
    bool operator!=(const Vector<T>& a, const Vector<T>& b) {
        return !(a == b);
    }

    template<typename T>
    bool operator<(const Vector<T>& a, const Vector<T>& b) {
        return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
    }

    template<typename T>
    bool operator>(const Vector<T>& a, const Vector<T>& b) {
        return b < a;
    }

    template<typename T>
    bool operator<=(const Vector<T>& a, const Vector<T>& b) {
        return !(b > a);
    }

    template<typename T>
    bool operator>=(const Vector<T>& a, const Vector<T>& b) {
        return !(a < b);
    }
}
