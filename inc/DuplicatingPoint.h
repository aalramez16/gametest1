
#pragma once

#include "Types.h"
#include "PointInterface.h"

class DuplicatingPoint final : public PointInterface {
private:
    int numDuplications;
    Shared<DuplicatingPoint> duplicate;
public:
    DuplicatingPoint(int numDuplications) : PointInterface(), numDuplications(numDuplications) {
        this->type="Duplicating Point";
        if (numDuplications > 0) {
            this->addDuplicate(numDuplications);
        }
    }
    explicit DuplicatingPoint(const Shared<PointInterface>& parent, int numDuplications) 
    : PointInterface(parent), numDuplications(numDuplications) {
        this->type="Duplicating Point";

        if (numDuplications > 0) {
            this->addDuplicate(numDuplications);
        }
    }

    void addDuplicate(int numDuplications) {
        this->duplicate = this->cloneAs<DuplicatingPoint>(numDuplications - 1);
    }

    Shared<DuplicatingPoint> clone() {
        return std::static_pointer_cast<DuplicatingPoint>(shared_from_this());
    }

    const str toString() {
        std::ostringstream oss;
        oss << this->PointInterface::toString();
        return oss.str();
    }
};