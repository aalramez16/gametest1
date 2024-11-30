#pragma once

#include "Types.h"
#include "PointInterface.h"

class PointNode final : public PointInterface {
public:
    PointNode() : PointInterface() {}
    explicit PointNode(const Shared<PointInterface>& parent) : PointInterface(parent) {}
};

class ReflectingPointNode final : public PointInterface {
public:
    ReflectingPointNode() : PointInterface() {}
    explicit ReflectingPointNode(const Shared<PointInterface>& parent) : PointInterface(parent) {}
};

class DuplicatingPointNode final : public PointInterface {
public:
    DuplicatingPointNode() : PointInterface() {}
    explicit DuplicatingPointNode(const Shared<PointInterface>& parent) : PointInterface(parent) {}
};