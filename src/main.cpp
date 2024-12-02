#include "Point.h"
#include "DuplicatingPoint.h"
#include "ReflectingPoint.h"
#include "PointSystem.h"

#include <iostream>
#include <memory>

using pint = PointInterface;

int main() {
    std::cout << "Begin Program" << "\n\n";
    
    // Initialize the point system
    auto psys = std::make_unique<PointSystem>(pint::make<DuplicatingPoint>(2));

    // Create and register an orphaned reflecting point
    auto child1 = psys->registerPoint(pint::make<ReflectingPoint>());

    // Create and register an orphaned child point
    auto child2 = psys->registerPoint(pint::make<Point>());

    // Add the child to the reflecting point
    child1->addChild(child2);

    // Add the reflecting point to the root, a duplicatingPoint
    psys->getRoot()->addChild(child1);

    // List the IDs registered in the point system
    std::cout << psys->toString() << '\n';

    // List each point in the registry's details
    for (auto& point : psys->getRegistry()) {
        std::cout << point->toString() << '\n';
    }

    // std::cout << psys->getRoot()->toString() << std::endl;

    return 0;
}