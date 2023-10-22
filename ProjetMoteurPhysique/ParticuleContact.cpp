#include "ParticuleContact.h"
#include "Particule.h"

void ParticuleContact::Resolve(float duration)
{
	ResolveVelocity(duration);
	ResolveInterpenetration();
}

float ParticuleContact::CalculateSeparatingVelocity()
{
	Vecteur3D relativeVelocity = particules[0]->getVitesse();
	if (particules[1])
		relativeVelocity = relativeVelocity - particules[1]->getVitesse();

	return relativeVelocity.produitScalaire(contactNormal);
}

void ParticuleContact::ResolveVelocity(float duration)
{
	// vitesse d'approche ou separation de deux objets
	float separatingVelocity = CalculateSeparatingVelocity();

	// pas de raprochement
	if (separatingVelocity > 0.f)
		return;

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

	float inverseMass = 1.0f / particules[0]->getMasse();
	if (particules[1])
		inverseMass += 1.0f / particules[1]->getMasse();

	if (inverseMass <= 0.f) return;

	float impulse = difVel / inverseMass;

	Vecteur3D implusePerIMass = contactNormal * impulse;
	Vecteur3D newVitesse(particules[0]->getVitesse() + implusePerIMass * (1.0f / particules[0]->getMasse()));
	particules[0]->setVitesse(newVitesse);

	if (particules[1]) {
		Vecteur3D newVitesse(particules[1]->getVitesse() + implusePerIMass * -(1.0f / particules[1]->getMasse()));
		particules[1]->setVitesse(newVitesse);
	}
}

void ParticuleContact::ResolveInterpenetration()
{
	if (penetration <= 0) // pas de penetration
		return;

	float inverseMass = 1.0f / particules[0]->getMasse();
	if (particules[1])
		inverseMass += 1.0f / particules[1]->getMasse();

	if (inverseMass <= 0.f) return;

	Vecteur3D ResolvPerIMass = contactNormal * (penetration / inverseMass);

	// taux de d�placement de chaque particules dans la penetration
	Vecteur3D* moveLenght[2];
	moveLenght[0] = new Vecteur3D(ResolvPerIMass * (1.0f / particules[0]->getMasse()));
	if (particules[1])
		moveLenght[1] = new Vecteur3D(ResolvPerIMass * (1.0f / particules[1]->getMasse()));

	// Mise � la position de non penetration
	Vecteur3D newPos(particules[0]->getVitesse() + *moveLenght[0]);
	particules[0]->setVitesse(newPos);
	if (particules[1]) {
		newPos = particules[1]->getVitesse() + *moveLenght[1];
		particules[1]->setVitesse(newPos);
	}
	delete[] moveLenght;
}