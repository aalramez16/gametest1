#include "PointInterface.h"
#include "ReflectingPoint.h"
#include "Reflection.h"
#include "DuplicatingPoint.h"

int PointInterface::lastId = 0;

ReflectingPoint::ReflectingPoint(int maxChildren) : PointInterface(maxChildren), reference(PointInterface::make<PointInterface>()), reflection(PointInterface::make<Reflection>(reference)) {
    this->type=" Reflecting Point";
    reference->setType("Reflecting Point Reference");
}

bool PointInterface::addChild(const Shared<ReflectingPoint>& child) {
    return this->appendToChildren(child, child->getReflection());
}

bool DuplicatingPoint::addChild(const Shared<ReflectingPoint>& child) {
    if (children.size() + 2 <= maxChildren) {
        return this->reference->addChild(child);
    }
    return false;
}

const Shared<PointInterface> ReflectingPoint::getReflection() {
    return reflection;
}