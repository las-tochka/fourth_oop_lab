#pragma once
#include <iostream>
#include <cmath>
#include <type_traits>
#include "concepts.h"

template<Scalar T>
class Point {
private:
    T x_, y_;
public:
    Point() : x_(0), y_(0) {}
    Point(T x, T y) : x_(x), y_(y) {}

    T x() const { return x_; }
    T y() const { return y_; }
    
    void print() const {

    auto round3 = [](auto val) { return std::round(static_cast<double>(val) * 1000.0) / 1000.0; };
    std::cout << "(" << round3(x_) << ", " << round3(y_) << ")";
    }
    friend std::istream& operator>>(std::istream& is, Point<T>& p) {
        is >> p.x_ >> p.y_;
        return is;
    }

    bool operator==(const Point& other) const {
        return x_ == other.x_ && y_ == other.y_;
    }
};
