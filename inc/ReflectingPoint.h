

#pragma once

#include "Types.h"
#include "PointInterface.h"

class ReflectingPoint final : public PointInterface {
private:
public:
    ReflectingPoint() : PointInterface() {
        this->type="Reflecting Point";
    }

    /**
     * Adds the child twice. One will be used as a reflection of the other
     * @param child a pointer to the child node
     */
    void addChild(const SharedPoint& child) override {
        for (int i = 0; i < 2; i++) {
            children.push_back(child);
        }
    }

    Shared<ReflectingPoint> clone() {
        return std::static_pointer_cast<ReflectingPoint>(shared_from_this());
    }

    str toString() override {
        std::ostringstream oss;
        oss << this->PointInterface::toString();
        return oss.str();
    }

};
