#pragma once
#include <iostream>
#include <vector>
#include <memory>

class Point {
protected:
	int id;
	std::unique_ptr<Point> parent;
	std::vector<std::unique_ptr<Point>> children;

public:
	/** Used as a counter for point ID incrementing */
	static int latestPointId;

	Point();  // Constructor
	virtual ~Point(); // Destructor

	Point(const Point&) = delete;
	Point& operator=(const Point&) = delete;

	Point(Point&&) noexcept; // Move constructor
	Point& operator=(Point&&) noexcept;   // Move assignment operator

	// Gets the ID for the point
	int getId() const;

	/**
	 * Sets the parent for a point
	 * @param parent a unique pointer to the parent node 
	 */
	void setParent(const std::unique_ptr<Point>& parent);

	const std::unique_ptr<Point>& getParent() const;

	/**
	 * Adds a child point to the point.
	 * @param child a std::unique_ptr pointer to the child node 
	 */
	void addChild(const std::unique_ptr<Point>& child);

	/**
	 * Removes a child from the point, if it exists.
	 * Deletes the child and all of its children.
	 * @param child a std::unique_ptr pointer to the child node 
	 */
	void removeChild(std::unique_ptr<Point>& child);

	/**
	 * Returns a vector of std::unique_ptr pointers to all children of this point.
	 */
	const std::vector<std::unique_ptr<Point>>& getChildren() const;

	static void establishParentChildRelationship(std::unique_ptr<Point> parent, std::unique_ptr<Point>& child);

	std::string toString() const;
};