#pragma once
#include "figure.h"
#include <memory>
#include <iostream>
#include <initializer_list>
#include <cmath>
#include <stdexcept>

template<Scalar T, size_t N>
class Polygon : public Figure<T> {
protected:
    std::unique_ptr<Point<T>[]> points;
public:
    Polygon() : points(std::make_unique<Point<T>[]>(N)) {}

    Polygon(std::initializer_list<Point<T>> init) : points(std::make_unique<Point<T>[]>(N)) {
        if (init.size() != N)
            throw std::invalid_argument("Неверное количество вершин");
        size_t i = 0;

        for (auto& p : init) {
            points[i++] = p;
        }
    }

    Polygon(const Polygon& other) : points(std::make_unique<Point<T>[]>(N)) {
        for (size_t i = 0; i < N; ++i)
            points[i] = other.points[i];
    }
    Polygon(Polygon&& other) noexcept : points(std::move(other.points)) {}

    Polygon& operator=(const Polygon& other) {
        if (this != &other) {
            for (size_t i = 0; i < N; ++i)
                points[i] = other.points[i];
        }
        return *this;
    }

    Polygon& operator=(Polygon&& other) noexcept {
        if (this != &other) points = std::move(other.points);
        return *this;
    }

    void input() {
        std::cout << "Введите координаты " << N << " вершин (x y):\n";
        for (size_t i = 0; i < N; ++i) {
            std::cin >> points[i];
        }
    }

    void print() const override {
        std::cout << N << "-угольник: ";
        for (size_t i = 0; i < N; ++i) {
            points[i].print();

            std::cout << " ";
        }
        std::cout << "\n";
    }

    Point<T> center() const override {
        T sx = 0, sy = 0;
        for (size_t i = 0; i < N; ++i) {
            sx += points[i].x();
            sy += points[i].y();
        }
        return Point<T>(sx / N, sy / N);
    }

    T area() const override {
        T s = 0;
        for (size_t i = 0; i < N; ++i) {
            const auto& a = points[i];
            const auto& b = points[(i + 1) % N];
            s += a.x() * b.y() - b.x() * a.y();
        }
        return std::abs(s) / 2;
    }

    bool operator==(const Polygon& other) const {
        for (size_t i = 0; i < N; ++i)
            if (!(points[i] == other.points[i]))
                return false;
        return true;
    }

    std::unique_ptr<Point<T>[]> vertices() const override {
        auto arr = std::make_unique<Point<T>[]>(N);
        for (size_t i = 0; i < N; ++i)
            arr[i] = points[i];
        return arr;
    }

    operator double() const override {
        return static_cast<double>(area());
    }

    size_t vertexCount() const override { return N; }
};

template<typename T> using Pentagon = Polygon<T, 5>;
template<typename T> using Hexagon  = Polygon<T, 6>;
template<typename T> using Octagon  = Polygon<T, 8>;
