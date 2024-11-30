#include "TransformingPoint.h"

void TransformingPoint::createSibling() {
    this->sibling = std::make_unique<Point>();
    establishParentChildRelationship(std::move(this->parent), this->sibling);
}

TransformingPoint::TransformingPoint() : Point() {
    createSibling();
}

void TransformingPoint::useSibling(const std::function<void(Point &)> &callback) {
    if (sibling) {
        callback(*sibling);
    } else {
        std::cerr << "Sibling does not exist." << std::endl;
    }
}

void TransformingPoint::addChild(const std::unique_ptr<Point>& child) {
    auto newChild = std::make_unique<Point>();

    Point::addChild(std::move(child));

    sibling->addChild(newChild);
}

