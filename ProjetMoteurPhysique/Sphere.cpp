#include "Sphere.h"

#include "collide_narrow.h"
#include "Plane.h"

Sphere::Sphere(float _radius) :
radius(_radius)
{
}

void Sphere::generateContacts(Primitive& secondPrimitaive, CollisionData* data)
{
    collide_narrow collide_narrow;
    if (const Sphere* two = dynamic_cast<const Sphere*>(&secondPrimitaive))
    {
        collide_narrow.sphereAndSphere(*this, *two, data);
    }
    else if (const Plane* plane = dynamic_cast<const Plane*>(&secondPrimitaive))
    {
        collide_narrow.sphereAndHalfSpace(*this, *plane, data);
    }
}
