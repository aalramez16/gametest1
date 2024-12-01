
#pragma once

#include "Types.h"
#include "PointInterface.h"

class DuplicatingPoint final : public PointInterface {
public:
    const str& type = "Duplicating Point";

    DuplicatingPoint() : PointInterface() {}
    explicit DuplicatingPoint(const Shared<PointInterface>& parent) : PointInterface(parent) {}

    Shared<DuplicatingPoint> clone() {
        return std::static_pointer_cast<DuplicatingPoint>(shared_from_this());
    }

    const str toString() {
        std::ostringstream oss;
        oss << "Type: " << type << "\n";
        oss << this->PointInterface::toString();
        return oss.str();
    }
};