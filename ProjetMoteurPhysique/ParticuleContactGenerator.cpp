#include "ParticuleContactGenerator.h"
#include "Particule.h"
#include "ParticuleContact.h"
#include "Vecteur3D.h"
#include <iostream>

#pragma region Particule Link

float ParticuleLink::currentLength() const 
{
	Vecteur3D relativePos = particules[0]->getPosition() - particules[1]->getPosition();
	return relativePos.calculNorme();
}

ParticuleCable::ParticuleCable(ParticuleContact* contact, float _maxLength, float _restitution)
{
	particules[0] = contact->particules[0];
	particules[1] = contact->particules[1];
	this->maxLength = _maxLength;
	this->restitution = _restitution;
}

#pragma endregion

#pragma region Particule Cable

unsigned ParticuleCable::addContact(ParticuleContact* contact, unsigned int limit) const 
{
	float length = currentLength();

	if (length < maxLength) return 0;

	//si trop tendu, alors on continue
	contact->particules[0] = particules[0];
	contact->particules[1] = particules[1];

	/*Vecteur3D normal = particules[1]->getPosition() - particules[0]->getPosition();
	normal.calculVecteurUnitaire();*/
	float deltaX = contact->particules[1]->getPosition().getX() - contact->particules[0]->getPosition().getX();
    float deltaY = contact->particules[1]->getPosition().getY() - contact->particules[0]->getPosition().getY();
    float deltaZ = contact->particules[1]->getPosition().getZ() - contact->particules[0]->getPosition().getZ();

    float temp = std::sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);

    contact->contactNormal = Vecteur3D(deltaX / temp, deltaY / temp, deltaZ / temp);
	//contact->contactNormal = normal;

	contact->penetration = length - maxLength;
	contact->restitution = restitution;

	return 1;
}

#pragma endregion


#pragma region Particule Rod

ParticuleRod::ParticuleRod(ParticuleContact* contact, float Length)
{
	particules[0] = contact->particules[0];
	particules[1] = contact->particules[1];
	this->length = Length;
}

unsigned ParticuleRod::addContact(ParticuleContact* contact, unsigned int limit) const
{
	float currentLeng = currentLength();

	if (currentLeng == length) return 0;

	contact->particules[0] = particules[0];
	contact->particules[1] = particules[1];

	/*Vecteur3D normal = particules[1]->getPosition() - particules[0]->getPosition();
	normal.calculVecteurUnitaire();*/

	float deltaX = contact->particules[1]->getPosition().getX() - contact->particules[0]->getPosition().getX();
	float deltaY = contact->particules[1]->getPosition().getY() - contact->particules[0]->getPosition().getY();
	float deltaZ = contact->particules[1]->getPosition().getZ() - contact->particules[0]->getPosition().getZ();

	float temp = std::sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);

	if (currentLeng > length)
	{
		//contact->contactNormal = normal;
		contact->contactNormal = Vecteur3D(deltaX / temp, deltaY / temp, deltaZ / temp);
		contact->penetration = currentLeng - length;
	}
	else
	{
		//contact->contactNormal = normal * -1.f;
		contact->contactNormal = Vecteur3D(deltaX / temp, deltaY / temp, deltaZ / temp) * -1.f;
		contact->penetration = length - currentLeng;
	}

	// 0 elasticite car c'est une distance fixe
	contact->restitution = 0;

	return 1;
}

#pragma endregion

NaiveParticuleContactGenerator::NaiveParticuleContactGenerator(float _radius, std::vector<Particule*> _particules)
{
	this->radius = _radius;
	this->particules = _particules;
}

unsigned int NaiveParticuleContactGenerator::addContact(ParticuleContact* contact, unsigned int limit) const
{

	// Check Temporaire de contact entre deux Particule definis
	float deltaX = contact->particules[0]->getPosition().getX() - contact->particules[1]->getPosition().getX();
	float deltaY = contact->particules[0]->getPosition().getY() - contact->particules[1]->getPosition().getY();
	float deltaZ = contact->particules[0]->getPosition().getZ() - contact->particules[1]->getPosition().getZ();

	float temp = std::sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);

	contact->contactNormal = Vecteur3D(deltaX / temp, deltaY / temp, deltaZ / temp);
	contact->penetration = radius - temp;
	if (contact->penetration < 0.f) contact->penetration = 0.f;

	return 1;
}
