#pragma once

#include "Types.h"
#include "PointInterface.h"

class Reflection;

class ReflectingPoint : public PointInterface {
private:
    SharedPoint reference;
    const Shared<Reflection> reflection;
public:
    ReflectingPoint();

    Shared<ReflectingPoint> clone() {
        return std::static_pointer_cast<ReflectingPoint>(shared_from_this());
    }

    void addChild(const SharedPoint& child) override {
        this->reference->addChild(child);
    }

    const std::vector<Shared<PointInterface>>& getChildren() override {
        return reference->getChildren();
    }

    std::string toString() override {
        std::ostringstream oss;
        oss << "Type: " << type << "\n";

        oss << "ID: " << id << "\n";

        // List children IDs
        if (!getChildren().empty()) {
            oss << "Children IDs: [";
            for (const auto& child : getChildren()) {
                oss << child->getId() << ", ";
            }
            // Safely remove the trailing comma and space
            oss.seekp(-2, std::ios_base::end);
            oss << "]";
        } else {
            oss << "Children IDs: []";
        }
        oss << std::endl;
        return oss.str();
    }

    [[nodiscard]] const Shared<PointInterface> getReference() {
        return this->reference;
    }
    
    [[nodiscard]] const Shared<PointInterface> getReflection();

};