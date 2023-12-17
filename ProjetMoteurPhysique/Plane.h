#pragma once
#include "Primitive.h"

class CorpsRigide;

class Plane : public Primitive
{
public:
    Plane(const Vecteur3D& _normal, float _offset);
    
    Vecteur3D normal;
    float offset;
};
