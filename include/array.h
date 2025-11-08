#pragma once
#include <memory>
#include <utility>
#include <stdexcept>
#include "figure.h"

template<class T>
class Array {
private:
    std::shared_ptr<T[]> data;
    size_t size_;
    size_t capacity_;

    void resize(size_t new_capacity) {
        std::shared_ptr<T[]> new_data(new T[new_capacity], std::default_delete<T[]>());
        for (size_t i = 0; i < size_; ++i)
            new_data[i] = std::move(data[i]);
        data = std::move(new_data);
        capacity_ = new_capacity;
    }

public:
    Array(size_t capacity = 2) : size_(0), capacity_(capacity) {
        data = std::shared_ptr<T[]>(new T[capacity_], std::default_delete<T[]>());
    }

    void push_back(const T& value) {
        if (size_ >= capacity_)
            resize(capacity_ * 2);
        data[size_++] = value;
    }

    void remove(size_t index) {
        if (index >= size_)
            throw std::out_of_range("Неверный индекс");
        for (size_t i = index; i < size_ - 1; ++i)
            data[i] = std::move(data[i + 1]);
        --size_;
    }

    size_t size() const { return size_; }
    T& operator[](size_t index) {
        if (index >= size_)
            throw std::out_of_range("Неверный индекс");
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size_)
            throw std::out_of_range("Неверный индекс");
        return data[index];
    }
    double totalArea() const {
        double total = 0;
        for (size_t i = 0; i < size_; ++i) {
            
            if constexpr (std::is_same_v<T, std::shared_ptr<Figure<double>>>) {
                if (data[i]) total += data[i]->area();
            } else {
                total += static_cast<double>(data[i]);
            }
        }
        return total;
    }
};
