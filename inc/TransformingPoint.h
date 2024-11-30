#pragma once
#include "Point.h"
#include <memory>
#include <functional>

class TransformingPoint : public Point {
protected:
    std::unique_ptr<Point>& sibling;
    void createSibling();
public:
    TransformingPoint();
    void useSibling(const std::function<void(Point&)>& callback);

    void addChild(const std::unique_ptr<Point>& child);
};
