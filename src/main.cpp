// maptest1.cpp : This file contains the 'main' function. Program execution begins and ends there.
// ^ it's called main.cpp, this is implied 😆

#include "Point.h"

#include <iostream>
#include <memory>

int main() {
    // Don't use `std::endl` more than once per scope
    // It does more than just add a newline and is notoriously inefficient.
    std::cout << "Begin Program" << '\n'; /*std::endl;*/

    // Create a parent point
    const auto parent = IPoint::Create<NormalPoint>();
    // add a couple of points to the parent
    const auto child1 = parent->addChild<NormalPoint>();
    const auto child2 = parent->addChild<NormalPoint>();
    const auto child3 = parent->addChild<NormalPoint>();

    std::cout << parent->toString() << '\n';

    // Cloning
    const Shared<IPoint> parentClone = parent->clone();
    std::cout << parentClone->toString() << '\n';

    // Cloning with specific type
    const Shared<NormalPoint> parentCloneAs = parent->cloneAs<NormalPoint>();
    std::cout << parentCloneAs->toString() << '\n';

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
