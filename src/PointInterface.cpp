#include "PointInterface.h"
#include "ReflectingPoint.h"
#include "Reflection.h"
#include "Point.h"

int PointInterface::lastId = 0;

ReflectingPoint::ReflectingPoint() : PointInterface(),reference(PointInterface::make<Point>()), reflection(PointInterface::make<Reflection>(reference)) {
    this->type=" Reflecting Point";
    reference->setType("Reflecting Point Reference");
}

void PointInterface::addChild(const Shared<ReflectingPoint>& child) {
    children.push_back(child);
    children.push_back(child->getReflection());
}

const Shared<PointInterface> ReflectingPoint::getReflection() {
    return reflection;
}