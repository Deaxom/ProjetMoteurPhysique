﻿#include "Plane.h"
#include "collide_narrow.h"
#include "Sphere.h"
#include "Box.h"

Plane::Plane(const Vecteur3D& _normal, float _offset) :
normal(_normal), offset(_offset)
{
}

void Plane::generateContacts(Primitive& secondPrimitaive, CollisionData* data)
{
    collide_narrow collide_narrow;
    if (Sphere* two = dynamic_cast<Sphere*>(&secondPrimitaive))
    {
        collide_narrow.sphereAndHalfSpace(*two, *this, data);
    }
    if (Box* two = dynamic_cast<Box*>(&secondPrimitaive))
    {
        collide_narrow.planeAndBox(*two, *this, data);
    }
}
