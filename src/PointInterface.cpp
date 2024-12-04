#include "PointInterface.h"
#include "NewReflectingPoint.h"
#include "Reflection.h"
#include "Point.h"

int PointInterface::lastId = 0;

NewReflectingPoint::NewReflectingPoint() : PointInterface(),reference(PointInterface::make<Point>()), reflection(PointInterface::make<Reflection>(reference)) {
    this->type="New Reflecting Point";
    reference->setType("Reflecting Point Reference");
}

void PointInterface::addChild(const Shared<NewReflectingPoint>& child) {
    children.push_back(child);
    children.push_back(child->getReflection());
}

const Shared<PointInterface> NewReflectingPoint::getReflection() {
    return reflection;
}