#include "Point.h"
#include "DuplicatingPoint.h"
#include "NewReflectingPoint.h"
#include "PointSystem.h"

#include <memory>

using pint = PointInterface;

int main() {
    std::cout << "Begin Program" << "\n\n";
    
    // Initialize the point system
    auto psys = std::make_unique<PointSystem>(pint::make<Point>());
    psys->getRoot()->setType("Root");

    // Create and register an orphaned reflecting point
    auto reflectingPoint = psys->registerPoint<NewReflectingPoint>(pint::make<NewReflectingPoint>());

    // Add the reflecting point to the root, a duplicatingPoint
    psys->getRoot()->addChild(reflectingPoint);

    auto reflectingPointChild = psys->registerPoint(pint::make<Point>());
    reflectingPointChild->setType("Child of Reflecting Point");
    reflectingPoint->addChild(reflectingPointChild);

    // List the IDs registered in the point system
    std::cout << psys->toString() << '\n';

    // List each point in the registry's details
    for (auto& point : psys->getRegistry()) {
        std::cout << point->toString() << '\n';
    }

    // std::cout << psys->getRoot()->toString() << std::endl;

    return 0;
}