

#pragma once

#include "Types.h"
#include "PointInterface.h"

class ReflectingPoint final : public PointInterface {
public:
    const str& type = "Reflecting Point";

    ReflectingPoint() : PointInterface() {}
    explicit ReflectingPoint(const Shared<PointInterface>& parent) : PointInterface(parent) {}

    const str toString() {
        std::ostringstream oss;
        oss << "Type: " << type << "\n";
        oss << this->PointInterface::toString();
        return oss.str();
    }
};
