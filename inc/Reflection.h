#pragma once

#include "Types.h"
#include "PointInterface.h"

class Reflection final : public PointInterface {
private:
    SharedPoint reference;
public:
    Reflection() = delete;
    Reflection(const SharedPoint& reference, int maxChildren=3) : PointInterface(maxChildren), reference(reference) {
        this->type="Reflection";
    }

    const std::vector<Shared<PointInterface>>& getChildren() override {
        return reference->getChildren();
    }

    Shared<Reflection> clone() {
        return std::static_pointer_cast<Reflection>(shared_from_this());
    }

    bool addChild(const SharedPoint& child) override {
        return this->reference->addChild(child);
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
};