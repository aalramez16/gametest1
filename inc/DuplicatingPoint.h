#pragma once
#include "Point.h"
#include <memory>
#include <functional>
#include <vector>

class DuplicatingPoint : public Point {
protected:
    int duplicationAmount;
public:
    DuplicatingPoint(int duplicationAmount);

    void createDuplicates();
};