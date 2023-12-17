#pragma once
#include "Matrix3x4.h"

class CorpsRigide;

class Primitive
{
public:
    Primitive();
    
    CorpsRigide *corpsRigide;
    Matrix3x4 offset;
};
