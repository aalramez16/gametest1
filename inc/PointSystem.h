#pragma once

#include "Types.h"
#include "PointInterface.h"

#include <vector>

class PointSystem {
private:
    // Holds all the actual points
    std::vector<SharedPoint> pointRegistry;

    // Pointer to the root
    SharedPoint root;

public:
    PointSystem() = default;
    PointSystem(const SharedPoint& root) : root(root) {
        this->registerPoint(root);
    }

    /**
     *  @brief Adds a `std::shared_ptr<PointInterface>` to the `pointRegistry`
     *  @param point a `std::shared_ptr` to the `PointInterface`
     */
    const SharedPoint& registerPoint(const SharedPoint& point) {
        pointRegistry.push_back(point);
        return point;
    }

    const SharedPoint& getRoot() {
        return this->root;
    }

    SharedPoint getPointById(const int id) {
        auto it = std::find_if(pointRegistry.begin(), pointRegistry.end(),
            [id](const SharedPoint& point) {
                return point->getId() == id;
            });

        // If found, return the pointer, otherwise return nullptr
        if (it != pointRegistry.end()) {
            return *it;
        } else {
            return nullptr;
        }
    }

};