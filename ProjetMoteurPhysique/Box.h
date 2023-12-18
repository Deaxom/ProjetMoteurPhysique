#pragma once
#include <complex>

#include "Primitive.h"
#include "Vecteur3D.h"

class Box : public Primitive
{
public:
    Box(Vecteur3D _halfSize);

    Vecteur3D halfSize;

    void generateContacts(Primitive& secondPrimitaive, CollisionData* data) override;

    float projectBoxOntoAxis(Vecteur3D& axis);
};
