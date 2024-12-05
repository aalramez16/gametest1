#pragma once

#include "Types.h"
#include <vector>
#include <memory>
#include <sstream>

#include <iostream>

// Forward Declare for concept templating
class PointInterface;
class ReflectingPoint;

template<typename T>
concept PointLikeObject = requires(T t) { std::is_base_of_v<PointInterface, T>; };

using SharedPoint = Shared<PointInterface>;

// We want to define a contract that a Point instance should follow
// without associating the interface with a specific type of point.
// i.e. -> decouple
class PointInterface : public std::enable_shared_from_this<PointInterface> {
private:
    static int lastId;
protected:
    str type = "Base";
    int id;
    std::vector<Shared<PointInterface>> children;

public:
    PointInterface() : id(lastId++) {}
    virtual ~PointInterface() {
        children.clear();
    }

    // Throw a warning if you call this without storing the return value
    virtual int getId() const {
        return id;
    }

    /**
     * Adds a child point to the point.
     * @param child a std::unique_ptr pointer to the child node
     */
    virtual void addChild(const SharedPoint& child) {
        children.push_back(child);
    }

    void addChild(const Shared<ReflectingPoint>& child);

    /**
     * Removes a child from the point, if it exists.
     * Deletes the child and all of its children.
     * @param child a std::unique_ptr pointer to the child node
     */
    void removeChild(const Shared<PointInterface>& child) {
        // You can simplify this a lot if you just use the STL erase function.
        // It'll automatically compare the pointer addresses
        std::erase(children, child);
    }

    /**
     * Returns a vector of std::unique_ptr pointers to all children of this point.
     */
    virtual const std::vector<Shared<PointInterface>>& getChildren() {  // don't need second const
        // const is fine here unless you need to modify this vector, then you'd just return a
        // reference
        return children;
    }

    virtual void setChildren(const std::vector<Shared<PointInterface>>& children) {
        this->children = children;
    }

    void setType(const str& type) {
        this->type = type;
    }

    virtual std::string toString() {
        std::ostringstream oss;
        oss << "Type: " << type << "\n";

        oss << "ID: " << id << "\n";

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
        oss << std::endl;
        return oss.str();
    }

    // These are just some different ideas for modifying this point instance

    // ex:
    // auto point = std::make_unique<PointInterface>();
    // auto child = point->addChild<DuplicatePoint>(10);
    template<PointLikeObject T, typename... Args>
    Shared<T> addChild(Args&&... args) {
        auto child = std::make_shared<T>(shared_from_this(), std::forward<Args>(args)...);
        children.push_back(child);
        return child;
    }


    // Provide an easy method of converting to a subclass of PointInterface
    template<PointLikeObject T>
    Shared<T> as() {
        return std::dynamic_pointer_cast<T>(shared_from_this());
    }

    template<PointLikeObject T, typename... Args>
    static Shared<T> make(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    Shared<PointInterface> clone() {
        return shared_from_this();
    }

    template<PointLikeObject T, typename... Args>
    Shared<T> cloneAs(Args&&... args) {
        const auto ptr = clone();
        return std::make_shared<T>(ptr, std::forward<Args>(args)...);
    }
};