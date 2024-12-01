#pragma once

#include "Types.h"
#include "PointInterface.h"

class Point final : public PointInterface {
public:
    const str& type = "Point";

    Point() : PointInterface() {}
    explicit Point(const Shared<PointInterface>& parent) : PointInterface(parent) {}

    Shared<Point> clone() {
        return std::static_pointer_cast<Point>(shared_from_this());
    }

    const str toString() {
        std::ostringstream oss;
        oss << "Type: " << type << "\n";
        oss << this->PointInterface::toString();
        return oss.str();
    }
};