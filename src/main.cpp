#include "Point.h"
#include "DuplicatingPoint.h"
#include "ReflectingPoint.h"
#include "PointSystem.h"

#include <iostream>
#include <memory>

using pint = PointInterface;

int main() {
    std::cout << "Begin Program" << "\n\n";
    
    auto psys = std::make_unique<PointSystem>(pint::make<ReflectingPoint>());

    auto child = psys->registerPoint(pint::make<Point>());

    psys->getRoot()->addChild(child);

    std::cout << psys->getRoot()->toString() << std::endl;

    return 0;
}