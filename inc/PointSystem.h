#pragma once

#include "Types.h"
#include "PointInterface.h"

#include <vector>
#include <typeinfo>

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
    PointSystem(const Shared<DuplicatingPoint>& root) : root(root) {
        this->registerPoint(root);
        this->registerPoint(root->getReference());
        for (auto& duplicate : root->getDuplicates()) {
            this->registerPoint(duplicate);
        }
    }

    [[nodiscard]] const std::vector<SharedPoint>& getRegistry() {
        return pointRegistry;
    }

    /**
     *  @brief Adds a `std::shared_ptr<PointInterface>` to the `pointRegistry`
     *  @param point a `std::shared_ptr` to the `PointInterface`
     */
    template <typename T>
    const Shared<T>& registerPoint(const Shared<T>& point) {
        pointRegistry.push_back(point);
        return point;
    }

    template<>
    const Shared<NewReflectingPoint>& registerPoint(const Shared<NewReflectingPoint>& point) {
        pointRegistry.push_back(point);
        pointRegistry.push_back(point->getReference());
        pointRegistry.push_back(point->getReflection());
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

    str toString() {
        std::ostringstream oss;
        // List children IDs
        oss << "POINT REGISTRY:" << '\n';
        if (!pointRegistry.empty()) {
            oss << "Point IDs: [";
            for (const auto& point : pointRegistry) {
                oss << point->getId() << ", ";
            }
            // Safely remove the trailing comma and space
            oss.seekp(-2, std::ios_base::end);
            oss << "]";
        } else {
            oss << "Point IDs: []";
        }
        oss << std::endl;
        return oss.str();
    }

};