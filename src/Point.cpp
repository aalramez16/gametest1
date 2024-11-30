#include "Point.h"
#include <algorithm>
#include <sstream>
#include <numeric>

int Point::latestPointId = 0;

// Constructor
Point::Point() : id(latestPointId++), parent(nullptr) {}

// Destructor
Point::~Point() {
    children.clear();
}

// Move Constructor
Point::Point(Point&& other) noexcept :
    id(other.id), // assign ID in move
    parent(std::move(other.parent)), // assign parent in move
    children(std::move(other.children)) {
        other.id = -1;
}

// Move Assignment Operator
Point& Point::operator=(Point&& other) noexcept {
    if (this != &other) {
        id = other.id;
        parent = std::move(other.parent);
        children = std::move(other.children);

        other.id = -1;
    }
    return *this;
}

int Point::getId() const {
    return id;
}

void Point::setParent(const std::unique_ptr<Point>& parent) {
    this->parent = parent;
}

const std::unique_ptr<Point>& Point::getParent() const {
	return parent;
}

void Point::addChild(const std::unique_ptr<Point>& child) {
    children.push_back(child);
}

void Point::removeChild(std::unique_ptr<Point>& child) {
    // Find and remove the child
    auto it = std::remove_if(children.begin(), children.end(),
        [&child](const std::unique_ptr<Point>& ptr) { return ptr.get() == child.get(); });

    if (it != children.end()) {
        children.erase(it, children.end());  // Remove the child from the vector
    }
}

const std::vector<std::unique_ptr<Point>>& Point::getChildren() const {
    return children;
}

void Point::establishParentChildRelationship(std::shared_ptr<Point> parent, std::unique_ptr<Point>& child) {
    child->setParent(parent);
    parent->addChild(child);
}

std::string Point::toString() const {
    std::ostringstream oss;
    oss << "ID: " << id << std::endl;

    // Check if the parent exists
    if (parent) {
        oss << "Parent ID: " << parent->getId() << std::endl;
    } else {
        oss << "Parent ID: None" << std::endl;
    }

    // List children IDs
    if (!children.empty()) {
        oss << "Children IDs: [";
        for (const auto& child : children) {
            oss << child->getId() << ", ";
        }
        // Safely remove the trailing comma and space
        oss.seekp(-2, std::ios_base::end);
        oss << "]";
    } else {
        oss << "Children IDs: []";
    }

    return oss.str();
}

