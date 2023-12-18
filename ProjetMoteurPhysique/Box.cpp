#include "Box.h"

#include "collide_narrow.h"
#include "Plane.h"
#include "Sphere.h"

Box::Box(Vecteur3D _halfSize) :
halfSize(_halfSize)
{
}

void Box::generateContacts(Primitive& secondPrimitaive, CollisionData* data)
{
    collide_narrow collide_narrow;
    if (const Sphere* sphere = dynamic_cast<const Sphere*>(&secondPrimitaive))
    {
        collide_narrow.sphereBoxCollider(*sphere, *this, data);
    }
    else if (Plane* plane = dynamic_cast<Plane*>(&secondPrimitaive))
    {
        collide_narrow.planeAndBox(*this, *plane, data);
    }
    else if (Box* box = dynamic_cast<Box*>(&secondPrimitaive))
    {
        collide_narrow.boxBoxCollider(*this, *box, data);
    }
}

float Box::projectBoxOntoAxis(Vecteur3D& axis)
{
    float projectedSize = halfSize.getX() * std::abs(axis.produitScalaire(Vecteur3D(1.0f, 0.0f, 0.0f))) +
                        halfSize.getY() * std::abs(axis.produitScalaire(Vecteur3D(0.0f,1.0f,0.0f))) +
                        halfSize.getZ() * std::abs(axis.produitScalaire(Vecteur3D(0.0f, 0.0f, 1.0f)));

    return projectedSize;
}
