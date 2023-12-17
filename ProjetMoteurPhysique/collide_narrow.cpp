#include "collide_narrow.h"

#include "Box.h"
#include "CollisionData.h"
#include "Contact.h"
#include "CorpsRigide.h"
#include "Plane.h"
#include "Sphere.h"
#include "Vecteur3D.h"
#include "Matrix3x4.h"

void collide_narrow::CheckRealCollision(Primitive& _one, Primitive& _two, CollisionData* data)
{
    if (Sphere* one = dynamic_cast<Sphere*>(&_one))
    {
        one->generateContacts(_two, data);
    }
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

    if (distance > sphere.radius)
    {
        std::cout << "No Collide" << std::endl;
        return 0;
    }
    
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

unsigned collide_narrow::planeAndBox(const Sphere& sphere, const Plane& plane, CollisionData* data)
{
    return 0;
}

unsigned collide_narrow::sphereBoxCollider(const Sphere& sphere, Box& box, CollisionData* data)
{
    // Convertion du centre du sphere en coordonné de la box
    Vecteur3D relCenter = sphere.corpsRigide->getPosition() - box.corpsRigide->getPosition();

    // Resserrage des coordonnés du point par rapport à la box
    // Pour X :
    float distX = relCenter.getX();
    if (distX > box.halfSize.getX()) distX = box.halfSize.getX();
    if (distX < -box.halfSize.getX()) distX = -box.halfSize.getX();

    // Pour Y :
    float distY = relCenter.getY();
    if (distY > box.halfSize.getY()) distY = box.halfSize.getY();
    if (distY < -box.halfSize.getY()) distY = -box.halfSize.getY();

    // Pour Z :
    float distZ = relCenter.getZ();
    if (distZ > box.halfSize.getZ()) distZ = box.halfSize.getZ();
    if (distZ < -box.halfSize.getZ()) distZ = -box.halfSize.getZ();

    Vecteur3D closestPoint(distX, distY, distZ);
    Vecteur3D separation = relCenter - closestPoint;

    float size = separation.calculNorme();

    return 0;
}
