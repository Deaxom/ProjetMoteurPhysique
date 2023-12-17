#pragma once

struct CollisionData;
class Primitive;
class Sphere;
class Plane;

class collide_narrow
{
public:
    void generateContacts(const Primitive &firstPrimitive,
                        const Primitive &seconPrimitaive,
                        CollisionData *data);

    unsigned sphereAndSphere(const Sphere &one,
                            const Sphere &two,
                            CollisionData *data);

    unsigned sphereAndHalfSpace(const Sphere &sphere,
                            const Plane &plane,
                            CollisionData *data);
};
