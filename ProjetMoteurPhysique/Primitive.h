#pragma once
#include "Matrix3x4.h"

class CorpsRigide;

class Primitive
{
public:
    CorpsRigide *corpsRigide;
    Matrix3x4 offset;
};
