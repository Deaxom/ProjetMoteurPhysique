#include "CollisionResolver.h"
#include "CorpsRigide.h"
#include "CollisionData.h"
#include "Contact.h"



 void CollisionResolver::resolveCollision(CollisionData data) {
     double maxPenetration = 0;
     Contact* contactWithMaxPenetration;
     
     for (size_t i = 0; i < data.contacts.size(); ++i) {
         Contact* currentContact = data.contacts[i];

         if (currentContact->penetration > maxPenetration) {
             maxPenetration = currentContact->penetration;
             contactWithMaxPenetration = currentContact;
         }
     }
}