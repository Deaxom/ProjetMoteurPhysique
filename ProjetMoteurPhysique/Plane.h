#pragma once
#include "Primitive.h"

class Plane : public Primitive
{
public:
    Vecteur3D normal;
    float offset;
};
