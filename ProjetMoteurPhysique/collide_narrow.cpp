#include "collide_narrow.h"
#include "CollisionData.h"
#include "Contact.h"
#include "CorpsRigide.h"
#include "Plane.h"
#include "Sphere.h"
#include "Matrix3x4.h"

void collide_narrow::generateContacts(const Primitive& firstPrimitive, const Primitive& seconPrimitaive, CollisionData* data)
{
}

unsigned collide_narrow::sphereAndSphere(const Sphere& one, const Sphere& two, CollisionData* data)
{
    // Check si il y a des contacts
    if (data->contactLeft <= 0) return 0;

    Vecteur3D positionOne = one.corpsRigide->getPosition();
    Vecteur3D positionTwo = two.corpsRigide->getPosition();

    // Trouver vecteur entre les deux spheres
    Vecteur3D midline = positionTwo - positionOne;
    float size = midline.calculNorme();

    if (size <= 0.0f || size >= one.radius + two.radius)
    {
        return 0;
    }

    // Calcul manuelle de la normal
    Vecteur3D normal = midline * (1.0f/size);

    auto* contact = new Contact;
    contact->contactNormal = normal;
    contact->contactPoint = positionOne + midline * 0.5f;
    contact->penetration = one.radius + two.radius - size;
    contact->corpsRigide[0] = one.corpsRigide;
    contact->corpsRigide[1] = two.corpsRigide;

    data->contacts.push_back(contact);
    data->contactLeft--;

    std::cout << "Collide" << std::endl;

    return 1;
}

unsigned collide_narrow::sphereAndHalfSpace(const Sphere& sphere, const Plane& plane, CollisionData* data)
{
    // Check si il y a des contacts
    if (data->contactLeft <= 0) return 0;

    // Stockage position de la sphere
    Vecteur3D position = sphere.corpsRigide->getPosition();
    
    // Distance depuis la plane
    float distance = position.produitScalaire(plane.normal) - plane.offset;

    if (distance > sphere.radius) return 0;
    
    Vecteur3D contactPoint = position - plane.normal * (distance - sphere.radius);
    
    // Création Contact
    auto* contact = new Contact;
    contact->contactNormal = plane.normal;
    contact->penetration = sphere.radius - distance;
    contact->contactPoint = contactPoint;
    contact->corpsRigide[0] = sphere.corpsRigide;
    contact->corpsRigide[1] = plane.corpsRigide;

    data->contacts.push_back(contact);
    data->contactLeft--;

    std::cout << "Collide" << std::endl;

    return 1;
}
