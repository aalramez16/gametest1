
#pragma once

#include "Types.h"
#include "PointInterface.h"

class DuplicatingPoint final : public PointInterface {
private:
    int numDuplications;
    int progenitorId;
    SharedPoint duplicate;
public:
    DuplicatingPoint(int numDuplications) : PointInterface(), numDuplications(numDuplications) {
        this->type="Duplicating Point";
        this->progenitorId = id;
        this->duplicate = nullptr;
        if (numDuplications > 0) {
            this->createDuplicate();
        }
    }

    DuplicatingPoint(int numDuplications, int progenitorId) 
    : PointInterface(),
      numDuplications(numDuplications),
      progenitorId(progenitorId) 
    {
        this->type="Duplicating Point";
        this->duplicate = nullptr;
        if (numDuplications > 0) {
            this->createDuplicate();
        }
    }

    void createDuplicate() {
        this->duplicate = PointInterface::make<DuplicatingPoint>(numDuplications - 1, progenitorId);
    }

    Shared<DuplicatingPoint> clone() {
        return std::static_pointer_cast<DuplicatingPoint>(shared_from_this());
    }

    void addChild(const SharedPoint& child) override {
        PointInterface::addChild(child);
        if (numDuplications > 0) {
            duplicate->addChild(child);
        }
    }

    const str toString() {
        std::ostringstream oss;
        oss << this->PointInterface::toString();
        return oss.str();
    }
};