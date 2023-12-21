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
    if (Box* one = dynamic_cast<Box*>(&_one))
    {
        one->generateContacts(_two, data);
    }
    if (Plane* one = dynamic_cast<Plane*>(&_one))
    {
        one->generateContacts(_two, data);
    }

    // Polyèdres
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
    contact->restitution = 0.8f;
    contact->contactNormal = normal;
    contact->contactPoint = positionOne + midline * 0.5f;
    contact->penetration = one.radius + two.radius - size;
    contact->corpsRigide[0] = one.corpsRigide;
    contact->corpsRigide[1] = two.corpsRigide;

    data->contacts.push_back(contact);
    data->contactLeft--;

    //std::cout << "Collide | ";

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
        //std::cout << "No Collide" << std::endl;
        return 0;
    }
    
    Vecteur3D contactPoint = position - plane.normal * (distance - sphere.radius);
    
    // Création Contact
    auto* contact = new Contact;
    contact->contactNormal = plane.normal;
    contact->penetration = sphere.radius - distance;
    contact->contactPoint = contactPoint;
    contact->restitution = 0.8f;
    contact->corpsRigide[0] = sphere.corpsRigide;
    contact->corpsRigide[1] = plane.corpsRigide;

    data->contacts.push_back(contact);
    data->contactLeft--;

    //std::cout << "Collide | ";

    return 1;
}

unsigned collide_narrow::planeAndBox(Box& box, Plane& plane, CollisionData* data)
{
    // Check si il y a des contacts
    if (data->contactLeft <= 0) return 0;
    
    // Vecteurs des coins de la boîte
    Vecteur3D corners[] = {
        Vecteur3D(-box.halfSize.getX(), -box.halfSize.getY(), -box.halfSize.getZ()),
        Vecteur3D(-box.halfSize.getX(), -box.halfSize.getY(), box.halfSize.getZ()),
        Vecteur3D(-box.halfSize.getX(), box.halfSize.getY(), -box.halfSize.getZ()),
        Vecteur3D(-box.halfSize.getX(), box.halfSize.getY(), box.halfSize.getZ()),
        Vecteur3D(box.halfSize.getX(), -box.halfSize.getY(), -box.halfSize.getZ()),
        Vecteur3D(box.halfSize.getX(), -box.halfSize.getY(), box.halfSize.getZ()),
        Vecteur3D(box.halfSize.getX(), box.halfSize.getY(), -box.halfSize.getZ()),
        Vecteur3D(box.halfSize.getX(), box.halfSize.getY(), box.halfSize.getZ())
    };

    // Transformation des coins de la boîte vers le repère du monde
    for (int i = 0; i < 8; ++i) {
        corners[i] = box.corpsRigide->getTransmationMatrice().TransformPosition(corners[i]);
    }

    // Vérifie si les coins de la boîte sont de part et d'autre du plan
    Contact* contact = new Contact;
    unsigned unsedContact = 0;
    for (int i = 0; i < 8; ++i) {
        float distance = corners[i].produitScalaire(plane.normal);
        std::cout << distance << "\n";

        if (distance <= plane.offset)
        {
            std::cout << "Collide | ";
            
            contact->contactPoint = corners[i] - plane.normal * (distance - plane.offset);
            contact->contactNormal = plane.normal;
            contact->penetration = plane.offset - distance;
            contact->restitution = 0.8f;
            contact->corpsRigide[0] = box.corpsRigide;
            contact->corpsRigide[1] = NULL;
            ++unsedContact;
            data->contacts.push_back(contact);
            if (unsedContact == data->contactLeft) return unsedContact;
        }
    }
    data->contactLeft -= unsedContact;
    return unsedContact;
}

unsigned collide_narrow::sphereBoxCollider(const Sphere& sphere, Box& box, CollisionData* data)
{
    // Check si il y a des contacts
    if (data->contactLeft <= 0) return 0;
    
    // Convertion du centre du sphere en coordonné de la box
    Vecteur3D relCenter = sphere.corpsRigide->getPosition() - box.corpsRigide->getPosition();

    // Resserrage des coordonnés du point par rapport à la box
    float dist;
    Vecteur3D closestPoint;
    // Pour X :
    dist = relCenter.getX();
    if (dist > box.halfSize.getX()) dist = box.halfSize.getX();
    if (dist < -box.halfSize.getX()) dist = -box.halfSize.getX();
    closestPoint.setX(dist);
    // Pour Y :
    dist = relCenter.getY();
    if (dist > box.halfSize.getY()) dist = box.halfSize.getY();
    if (dist < -box.halfSize.getY()) dist = -box.halfSize.getY();
    closestPoint.setY(dist);
    // Pour Z :
    dist = relCenter.getZ();
    if (dist > box.halfSize.getZ()) dist = box.halfSize.getZ();
    if (dist < -box.halfSize.getZ()) dist = -box.halfSize.getZ();
    closestPoint.setZ(dist);
    
    Vecteur3D separation = relCenter - closestPoint;

    float size = separation.calculNorme();

    if(size < sphere.radius)
    {
        Contact* contact = new Contact;
        contact->contactNormal = box.corpsRigide->getTransmationMatrice().TransformPosition(closestPoint) - sphere.corpsRigide->getPosition();
        contact->contactNormal.calculNorme();
        contact->contactPoint = box.corpsRigide->getTransmationMatrice().TransformPosition(closestPoint);
        contact->penetration = sphere.radius - separation.calculNorme();
        contact->restitution = 0.8f;
        contact->corpsRigide[0] = box.corpsRigide;
        contact->corpsRigide[1] = sphere.corpsRigide;

        
        data->contacts.push_back(contact);
        data->contactLeft--;
        
        return 1;
    }

    return 0;
}

unsigned collide_narrow::boxBoxCollider(Box& one, Box& two, CollisionData* data)
{
    // Axes de séparation potentiels
    Vecteur3D axes[] = {
        Vecteur3D(one.offset.Value(0, 0), one.offset.Value(1, 0), one.offset.Value(2, 0)),
        Vecteur3D(one.offset.Value(0, 1), one.offset.Value(1, 1), one.offset.Value(2, 1)),
        Vecteur3D(one.offset.Value(0, 2), one.offset.Value(1, 2), one.offset.Value(2, 2)),
        Vecteur3D(two.offset.Value(0, 0), two.offset.Value(1, 0), two.offset.Value(2, 0)),
        Vecteur3D(two.offset.Value(0, 1), two.offset.Value(1, 1), two.offset.Value(2, 1)),
        Vecteur3D(two.offset.Value(0, 2), two.offset.Value(1, 2), two.offset.Value(2, 2)),
        one.corpsRigide->getPosition() - two.corpsRigide->getPosition()
    };
    // Variables pour stocker les informations de collision
    float minOverlap = std::numeric_limits<float>::max();
    Vecteur3D collisionNormal;
    Vecteur3D collisionPoint;

    for (const Vecteur3D& axis : axes) {
        // Normalise l'axe de séparation
        Vecteur3D normalizedAxis = axis.calculVecteurUnitaire();

        // Projette les boîtes sur l'axe
        float projection1 = one.projectBoxOntoAxis(normalizedAxis);
        float projection2 = two.projectBoxOntoAxis(normalizedAxis);

        // Distance entre les centres projetée sur l'axe
        float centerSeparation = two.corpsRigide->getPosition().produitScalaire(normalizedAxis) - one.corpsRigide->getPosition().produitScalaire(normalizedAxis);

        // Somme des projections des demi-tailles
        float sumProjections = projection1 + projection2;

        // Calcule le chevauchement (overlap)
        float overlap = sumProjections - centerSeparation;

        // Si l'overlap est négatif, il y a séparation sur cet axe, pas de collision
        if (overlap < 0.0f) {
            return 0;
        }

        // Mise à jour des informations de collision si l'overlap est plus petit que le minimum trouvé jusqu'à présent
        if (overlap < minOverlap) {
            minOverlap = overlap;
            collisionNormal = normalizedAxis;
        }
    }

    // Calcule le point de contact
    collisionPoint = (one.corpsRigide->getPosition() + two.corpsRigide->getPosition()) * 0.5f;


    // Collision détectée
    Contact* contact = new Contact();
    contact->restitution = 0.8f;
    contact->penetration = minOverlap;
    contact->contactPoint = collisionPoint;
    contact->contactNormal = collisionNormal;
    contact->corpsRigide[0] = one.corpsRigide;
    contact->corpsRigide[1] = two.corpsRigide;
    data->contacts.push_back(contact);
    data->contactLeft--;

    return 1;
}

