#pragma once

#include "Types.h"
#include "PointInterface.h"

template<typename T>
requires std::is_default_constructible_v<T> && std::is_copy_assignable_v<T>
class DataPoint : public PointInterface {
protected:
    T data;
public:
    Point(T data, int maxChildren=3) : PointInterface(maxChildren), data(data) {
        this->type="Point";
    }

    Shared<Point> clone() {
        return std::make_shared<Point<T>>(data, maxChildren);
    }

    void setData(T data) {
        this->data = data;
    }

    const T& getData() {
        return this->data;
    }

    str toString() override {
        std::ostringstream oss;
        oss << this->PointInterface::toString();
        return oss.str();
    }
};