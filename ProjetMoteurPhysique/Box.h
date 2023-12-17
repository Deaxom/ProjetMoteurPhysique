#pragma once
#include "Primitive.h"
#include "Vecteur3D.h"

class Box : public Primitive
{
public:
    Box(const Vecteur3D& _halfSize);

    Vecteur3D halfSize;
};
