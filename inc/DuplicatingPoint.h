
#pragma once

#include "Types.h"
#include "PointInterface.h"

class DuplicatingPoint final : public PointInterface {
private:
    int numDuplications;
    Shared<Point> reference;
    Shared<DuplicatingPoint> duplicate;
    std::vector<Shared<PointInterface>> combinedChildren;
public:

    // Calling this constructor assumes you are the top of the chain
    DuplicatingPoint()
    : PointInterface(),
      numDuplications(1),
      reference(PointInterface::make<Point>())
    {
        this->type="Duplicating Point";
        createDuplicate();
    }

    // Calling this constructor assumes you are the top of the chain
    DuplicatingPoint(int numDuplications)
    : PointInterface(),
      numDuplications(numDuplications),
      reference(PointInterface::make<Point>())
    {
        this->type="Duplicating Point";
        createDuplicate();
    }

    // This will be the constructor called by duplicates
    DuplicatingPoint(int numDuplications, const Shared<Point>& reference) 
    : PointInterface(),
      numDuplications(numDuplications),
      reference(reference)
    {
        this->type="Duplicating Point";
        createDuplicate();
    }

    [[nodiscard]] const Shared<Point>& getReference() {
        return reference;
    }

    void createDuplicate() {
        if (numDuplications > 0) {
            this->duplicate = PointInterface::make<DuplicatingPoint>(numDuplications - 1, reference);
            PointInterface::addChild(this->duplicate);
        }
    }

    void addRealChild(const SharedPoint& child) {
        PointInterface::addChild(child);
    }

    void addChild(const SharedPoint& child) override {
        this->reference->addChild(child);
    }

    Shared<DuplicatingPoint> getDuplicate() {
        return this->duplicate;
    }

    void getDuplicates(std::vector<Shared<DuplicatingPoint>>& duplicates) {
        if (numDuplications == 0) return;
        else {
            duplicates.push_back(getDuplicate());
            return getDuplicate()->getDuplicates(duplicates);
        }
    }

    // a wrapper for the void getDuplicates()
    std::vector<Shared<DuplicatingPoint>> getDuplicates() {
        std::vector<Shared<DuplicatingPoint>> duplicates;
        getDuplicates(duplicates);
        return duplicates;
    }

    void combineChildren() {
        // Prevent multiple runs
        if (!combinedChildren.empty()) return;

        // Grab reference's children
        auto referenceChildren = reference->getChildren();

        // If this isn't a leaf node, also grab the next duplicate as a child
        if (numDuplications != 0) {
            std::vector<SharedPoint> combinedChildren;
            combinedChildren.reserve(referenceChildren.size() + 1); // Reserve space for efficiency
            combinedChildren.push_back(this->getDuplicate());
            combinedChildren.insert(combinedChildren.end(), referenceChildren.begin(), referenceChildren.end());
            this->combinedChildren = combinedChildren;
        } else {
            // Otherwise, the reference's children act as the only children to this node.
            this->combinedChildren = referenceChildren;
        }
    }

    const std::vector<Shared<PointInterface>>& getChildren() override {
        if (combinedChildren.size() == 0) {
            combineChildren();
        }
        return this->combinedChildren;
    }

    Shared<DuplicatingPoint> clone() {
        return std::static_pointer_cast<DuplicatingPoint>(shared_from_this());
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