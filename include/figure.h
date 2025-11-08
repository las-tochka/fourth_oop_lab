#pragma once
#include <memory>
#include <cstddef>
#include <type_traits>
#include "point.h"
#include "concepts.h"

template<Scalar T>
class Figure {
public:
    virtual ~Figure() = default;
    virtual void input() = 0;
    virtual T area() const = 0;
    virtual Point<T> center() const = 0;
    virtual operator double() const { return static_cast<double>(area()); }
    virtual size_t vertexCount() const = 0;
    virtual void print() const = 0;
    
    virtual std::unique_ptr<Point<T>[]> vertices() const = 0;
};
