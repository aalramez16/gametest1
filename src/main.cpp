#include "Point.h"
#include "DuplicatingPoint.h"

#include <iostream>
#include <memory>

int main() {
    std::cout << "Begin Program" << "\n\n";

    // Create a parent point
    const auto parent = PointInterface::Create<Point>();

    // add a couple of points to the parent
    const auto child1 = parent->addChild<Point>();
    const auto child2 = parent->addChild<DuplicatingPoint>();
    const auto child3 = parent->addChild<Point>();

    std::cout << parent->toString() << '\n';

    // Cloning
    const Shared<Point> parentClone = parent->clone();
    std::cout << parentClone->toString() << '\n';

    // Cloning with specific type
    const Shared<Point> parentCloneAs = parent->cloneAs<Point>();
    std::cout << parentCloneAs->toString() << '\n';

    std::cout << child2->toString() << '\n';

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add
//   existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln
//   file
