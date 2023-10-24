#include "ParticuleContact.h"
#include "Particule.h"
#include <iostream>

ParticuleContact::ParticuleContact()
{
	this->particules[0] = new Particule;
	this->particules[1] = new Particule;
	this->penetration = 0.f;
	this->contactNormal = Vecteur3D(0.0, 0.0, 0.0);
	this->restitution = 0.f;
}

void ParticuleContact::Resolve(float duration)
{
	ResolveVelocity(duration);
	ResolveInterpenetration();
}

float ParticuleContact::CalculateSeparatingVelocity()
{
	Vecteur3D relativeVelocity = particules[0]->getVitesse();
	if (particules[1])
		relativeVelocity = particules[1]->getVitesse() - relativeVelocity;

	return relativeVelocity.produitScalaire(contactNormal);
}

void ParticuleContact::ResolveVelocity(float duration)
{
	// vitesse d'approche ou separation de deux objets
	float separatingVelocity = CalculateSeparatingVelocity();

	// pas de raprochement
	if (separatingVelocity < 0.f)
		return;

	/*particules[0]->setVitesse(particules[0]->getVitesse() * -1 * restitution);
	particules[1]->setVitesse(particules[1]->getVitesse() * -1 * restitution);

	return;*/


	float restituedSepVel = -separatingVelocity * restitution;

	// Verification de l'acceleration qui genererai encore de la vitesse
	Vecteur3D accVel = particules[0]->getAcceleration();
	if (particules[1])
		accVel = accVel - particules[1]->getAcceleration();

	float accSepVel = accVel.produitScalaire(contactNormal) * duration;

	if (accSepVel < 0)
	{
		restituedSepVel += restitution * accSepVel;
		if (restituedSepVel < 0) restituedSepVel = 0;
	}

	float difVel = restituedSepVel - separatingVelocity;

	float inverseMass = 0.0f;
	if (particules[0]->getIsDynamic())
		inverseMass += 1.0f / particules[0]->getMasse();
	if (particules[1] && particules[1]->getIsDynamic())
		inverseMass += 1.0f / particules[1]->getMasse();

	if (inverseMass <= 0.f) return;

	float impulse = difVel / inverseMass;

	Vecteur3D implusePerIMass = contactNormal * impulse;

	if (particules[0]->getIsDynamic()) {
		Vecteur3D newVitesse(particules[0]->getVitesse() + implusePerIMass * -(1.0f / particules[0]->getMasse()));
		particules[0]->setVitesse(newVitesse);
	}

	if (particules[1] && particules[1]->getIsDynamic()) {
		Vecteur3D newVitesse(particules[1]->getVitesse() + implusePerIMass * (1.0f / particules[1]->getMasse()));
		particules[1]->setVitesse(newVitesse);
	}

	for (int i = 0; i < 2; i++)
	{
		CheckResting(i);
	}
}

void ParticuleContact::ResolveInterpenetration()
{
	if (penetration <= 0.01f) // pas de penetration
		return;

	float inverseMass = 1.0f / particules[0]->getMasse();
	if (particules[1])
		inverseMass += 1.0f / particules[1]->getMasse();

	if (inverseMass <= 0.f) return;

	Vecteur3D ResolvPerIMass = contactNormal * /*penetration;*/ (penetration / inverseMass);

	// taux de d�placement de chaque particules dans la penetration
	Vecteur3D moveLenght[2];
		moveLenght[0] = ResolvPerIMass * /* 0.5f;*/ (1.0f / particules[0]->getMasse());

	if (particules[1])
		moveLenght[1] = ResolvPerIMass * /*-0.5f;*/ -(1.0f / particules[1]->getMasse());

	// Mise � la position de non penetration
	Vecteur3D newPos(particules[0]->getPosition()+ moveLenght[0]);
	particules[0]->setPosition(newPos);
	if (particules[1]) {
		newPos = particules[1]->getPosition() + moveLenght[1];
		particules[1]->setPosition(newPos);
	}

	if (!particules[1]) return;

	float deltaX = particules[0]->getPosition().getX() - particules[1]->getPosition().getX();
	float deltaY = particules[0]->getPosition().getY() - particules[1]->getPosition().getY();
	float deltaZ = particules[0]->getPosition().getZ() - particules[1]->getPosition().getZ();

	float temp = std::sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);

	if (temp < 1.f && temp > -1.f) {
		std::cout << "still gap";
	}
}

void ParticuleContact::CheckResting(int i)
{
	float x = particules[i]->getVitesse().getX();
	float y = particules[i]->getVitesse().getY();
	float z = particules[i]->getVitesse().getZ();

	if (x <= particules[i]->getLastVitesse().getX() + 0.01f && x >= particules[i]->getLastVitesse().getX() - 0.01f)
	{
		x = 0.f;
	}
	if (y <= particules[i]->getLastVitesse().getY() + 0.01f && y >= particules[i]->getLastVitesse().getY() - 0.01f)
	{
		y = 0.f;
	}
	if (z <= particules[i]->getLastVitesse().getZ() + 0.01f && z >= particules[i]->getLastVitesse().getZ() - 0.01f)
	{
		z = 0.f;
	}

	particules[1]->setPosition(Vecteur3D(x, y, z));
}
