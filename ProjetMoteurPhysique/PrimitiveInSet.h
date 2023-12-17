#pragma once
#include <vector>

#include "Matrix3x4.h"
#include "Primitive.h"
#include "PrimitiveInSet.h"

class Primitive;

struct PrimitiveInSet
{
    Primitive *primitive;
    Matrix3x4 offset;
};

struct PrimitiveSet : public Primitive
{
    std::vector<PrimitiveInSet> primitives;
};
