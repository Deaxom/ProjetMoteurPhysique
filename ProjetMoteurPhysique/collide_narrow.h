#pragma once
#include "Primitive.h"

class Box;
struct CollisionData;
class Primitive;
class Sphere;
class Plane;

class collide_narrow
{
public:
    void CheckRealCollision(Primitive &one,
                            Primitive &two,
                            CollisionData *data);
    
    unsigned sphereAndSphere(const Sphere &one,
                            const Sphere &two,
                            CollisionData *data);

    unsigned sphereAndHalfSpace(const Sphere &sphere,
                            const Plane &plane,
                            CollisionData *data);

    unsigned planeAndBox(Box &box,
                        Plane &plane,
                        CollisionData *data);

    unsigned sphereBoxCollider(const Sphere &sphere,
                            Box &box,
                            CollisionData *data);
    
    unsigned boxBoxCollider(Box &one,
                            Box &two,
                            CollisionData *data);
};
