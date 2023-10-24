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

ParticuleLink::ParticuleLink()
{
	particules[0] = new Particule();
	particules[1] = new Particule();
}

ParticuleLink::~ParticuleLink()
{
}

ParticuleCable::ParticuleCable(ParticuleContact* contact, float _maxLength, float _restitution)
{
	particules[0] = contact->particules[0];
	particules[1] = contact->particules[1];
	this->maxLength = _maxLength;
	this->restitution = _restitution;
}

ParticuleCable::~ParticuleCable()
{
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

ParticuleRod::~ParticuleRod()
{
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

NaiveParticuleContactGenerator::~NaiveParticuleContactGenerator()
{
}

unsigned int NaiveParticuleContactGenerator::addContact(ParticuleContact* contact, unsigned int limit) const
{
	unsigned int utilisations = 0;

	for (int i = 0; i < particules.size(); ++i)
	{
		for (int j = i + 1; j < particules.size(); ++j)
		{
			Particule* A = particules[i];
			Particule* B = particules[j];

			// Check Temporaire de contact entre deux Particule definis
			float deltaX = A->getPosition().getX() - B->getPosition().getX();
			float deltaY = A->getPosition().getY() - B->getPosition().getY();
			float deltaZ = A->getPosition().getZ() - B->getPosition().getZ();
			float temp = std::sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);

			if (temp < radius) {
				if (utilisations < limit) {
					// Contact généré
					contact[utilisations].particules[0] = A;
					contact[utilisations].particules[1] = B;

					// Calcul de la normale et de la pénétration
					contact[utilisations].contactNormal = Vecteur3D(deltaX / temp, deltaY / temp, deltaZ / temp);
					contact[utilisations].penetration = radius - temp;
					if (contact[utilisations].penetration < 0.0f) contact[utilisations].penetration = 0.0f;
					contact[utilisations].restitution = 0.5f;

					utilisations++;
				}
				else {
					// Limite de contacts atteinte
					return utilisations;
				}
			}

			/*contact->contactNormal = Vecteur3D(deltaX / temp, deltaY / temp, deltaZ / temp);
			contact->penetration = radius - temp;
			if (contact->penetration < 0.f) contact->penetration = 0.f;*/


		}
	}
			return utilisations;
}

WallContactGenerator::WallContactGenerator(float _groundHeight, float wallMinX, float wallMinZ, std::vector<Particule*> _particules)
{
	this->groundHeight = _groundHeight;
	this->wallMinX = wallMinX;
	this->wallMinY = wallMinZ;
	this->particules = _particules;
}

WallContactGenerator::~WallContactGenerator()
{
}

unsigned int WallContactGenerator::addContact(ParticuleContact* contact, unsigned int limit) const
{
	unsigned int utilisations = 0;

	for (int i = 0; i < particules.size(); ++i)
	{
		Particule* A = particules[i];
		// Détection de la collision avec le sol
		if (A->getPosition().getY() < groundHeight) {
			contact[utilisations].particules[0] = A;
			contact[utilisations].particules[1] = nullptr;
			contact->contactNormal = Vecteur3D(0.0f, 1.0f, 0.0f); // Normale vers le haut (sol)
			contact->penetration = groundHeight - A->getPosition().getY();
			if (contact->penetration < 0.0f) contact->penetration = 0.0f;
			contact->restitution = 0.5f;
			utilisations++;
		}

		// Détection de la collision avec les murs
		float minX = -wallMinX;
		float maxX = wallMinX;
		float minZ = -wallMinY;
		float maxZ = wallMinY;

		float particuleX = A->getPosition().getX();
		float particuleY = A->getPosition().getY();

		if (particuleX < minX) {
			contact[utilisations].particules[0] = A;
			contact[utilisations].particules[1] = nullptr;
			contact->contactNormal = Vecteur3D(1.0f, 0.0f, 0.0f); // Normale vers la droite (mur)
			contact->penetration = minX - particuleX;
			if (contact->penetration < 0.0f) contact->penetration = 0.0f;
			utilisations++;
			contact->restitution = 0.5f;
		}
		else if (particuleX > maxX) {
			contact[utilisations].particules[0] = A;
			contact[utilisations].particules[1] = nullptr;
			contact->contactNormal = Vecteur3D(-1.0f, 0.0f, 0.0f); // Normale vers la gauche (mur)
			contact->penetration = particuleX - maxX;
			if (contact->penetration < 0.0f) contact->penetration = 0.0f;
			utilisations++;
			contact->restitution = 0.5f;
		}

		if (particuleY < minZ) {
			contact[utilisations].particules[0] = A;
			contact[utilisations].particules[1] = nullptr;
			contact->contactNormal = Vecteur3D(0.0f, 1.0f, .0f); // Normale vers l'avant (mur)
			contact->penetration = minZ - particuleY;
			if (contact->penetration < 0.0f) contact->penetration = 0.0f;
			utilisations++;
			contact->restitution = 0.5f;
		}
	}
	return utilisations;
}
