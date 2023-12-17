#pragma once
#include "Matrix3x4.h"

struct CollisionData;
class CorpsRigide;

class Primitive
{
public:
    Primitive();
    
    CorpsRigide *corpsRigide;
    Matrix3x4 offset;

    virtual void generateContacts(Primitive& secondPrimitaive, CollisionData* data) = 0;
};
