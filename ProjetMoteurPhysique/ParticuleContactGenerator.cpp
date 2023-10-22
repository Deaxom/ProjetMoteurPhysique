#include "ParticuleContactGenerator.h"
#include "Particule.h"
#include "ParticuleContact.h"
#include "Vecteur3D.h"

#pragma region Particule Link

float ParticuleLink::currentLength() const 
{
	Vecteur3D relativePos = particules[0]->getPosition() - particules[1]->getPosition();
	return relativePos.calculNorme();
}

#pragma endregion

#pragma region Particule Cable

unsigned ParticuleCable::addContact(ParticuleContact* contact, unsigned int limit) const 
{
	float length = currentLength();
	if (length < maxLength) return 0;

	contact->particules[0] = particules[0];
	contact->particules[1] = particules[1];

	Vecteur3D normal = particules[1]->getPosition() - particules[0]->getPosition();
	normal.calculVecteurUnitaire();
	contact->contactNormal = normal;

	contact->penetration = length - maxLength;
	contact->restitution = restitution;

	return 1;
}

#pragma endregion


#pragma region Particule Rod

unsigned ParticuleRod::addContact(ParticuleContact* contact, unsigned int limit) const
{
	float currentLeng = currentLength();

	if (currentLeng == length) return 0;

	contact->particules[0] = particules[0];
	contact->particules[1] = particules[1];

	Vecteur3D normal = particules[1]->getPosition() - particules[0]->getPosition();
	normal.calculVecteurUnitaire();

	if (currentLeng > length)
	{
		contact->contactNormal = normal;
		contact->penetration = currentLeng - length;
	}
	else
	{
		contact->contactNormal = normal;
		contact->penetration = length - currentLeng;
	}

	// 0 elasticite car c'est une distance fixe
	contact->restitution = 0;

	return 1;
}

#pragma endregion

