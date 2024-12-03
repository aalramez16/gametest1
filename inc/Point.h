#pragma once

#include "Types.h"
#include "PointInterface.h"

class Point final : public PointInterface {
public:
    Point() : PointInterface() {
        this->type="Point";
    }
    explicit Point(const Shared<PointInterface>& parent) : PointInterface(parent) {
        this->type="Point";
    }

    Shared<Point> clone() {
        return std::static_pointer_cast<Point>(shared_from_this());
    }

    str toString() override {
        std::ostringstream oss;
        oss << this->PointInterface::toString();
        return oss.str();
    }
};