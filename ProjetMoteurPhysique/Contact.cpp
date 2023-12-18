#include "Contact.h"
#include "CorpsRigide.h"

void Contact::ResolveInterpenetration() {
	if (penetration <= 0.01f) // pas de penetration
		return;

	float inverseMass = 0.f;
	if (corpsRigide[0]->getMasse() < 100)
		inverseMass = 1.0f / corpsRigide[0]->getMasse();
	if (corpsRigide[1] && corpsRigide[1]->getMasse() < 100)
		inverseMass += 1.0f / corpsRigide[1]->getMasse();

	if (inverseMass <= 0.f) return;

	Vecteur3D ResolvPerIMass = contactNormal * /*penetration;*/ (penetration / inverseMass);

	// taux de deplacement de chaque corpsRigide dans la penetration
	Vecteur3D moveLenght[2];
	if (corpsRigide[0]->getMasse() < 100)
		moveLenght[0] = ResolvPerIMass * /* 0.5f;*/ (1.0f / corpsRigide[0]->getMasse());

	if (corpsRigide[1] && corpsRigide[1]->getMasse() < 100)
		moveLenght[1] = ResolvPerIMass * /*-0.5f;*/ -(1.0f / corpsRigide[1]->getMasse());

	// Mise a la position de non penetration
	Vecteur3D newPos(corpsRigide[0]->getPosition() + moveLenght[0]);
	corpsRigide[0]->setPosition(newPos);
	if (corpsRigide[1] && corpsRigide[1]->getMasse() < 100) {
		newPos = corpsRigide[1]->getPosition() + moveLenght[1];
		corpsRigide[1]->setPosition(newPos);
	}

	if (!corpsRigide[1]) return;
}

void Contact::ResolveVelocity(float duration) {
	float separationVelocity = CalculateSeparatingVelocity();
	if (separationVelocity < 0) {
		return;
	}
	float restitutionVelocity = -separationVelocity * restitution;

	Vecteur3D accelerationCorpsRigide = corpsRigide[0]->getAcceleration();
	if (corpsRigide[1]) {
		accelerationCorpsRigide = accelerationCorpsRigide - corpsRigide[1]->getAcceleration();
	}

	float accelerationSeparation = accelerationCorpsRigide.produitScalaire(contactNormal) * duration;

	if (accelerationSeparation < 0) {
		restitutionVelocity += restitution * accelerationSeparation;
		if (restitutionVelocity < 0) restitutionVelocity = 0;
	}

	float differenceVelocity = restitutionVelocity - separationVelocity;

	float inverseMass = 0.0f;
	if (corpsRigide[0]->getMasse() < 100) // check si l'objet est mobile ou non via la masse
			inverseMass += 1.0f / corpsRigide[0]->getMasse(); 
	if (corpsRigide[1] && corpsRigide[1]->getMasse() < 100) // check si l'objet existe et est mobile ou non via la masse
		inverseMass += 1.0f / corpsRigide[1]->getMasse();

	if (inverseMass <= 0.f) return;

	float impulse = differenceVelocity / inverseMass;
	
	Vecteur3D impulsePerIMass = contactNormal * impulse;

	if (corpsRigide[0]->getMasse() < 100) {
		Vecteur3D newVitesse(corpsRigide[0]->getVitesse() + impulsePerIMass * -(1.0f / corpsRigide[0]->getMasse()));
		corpsRigide[0]->setVitesse(newVitesse);
	}

	if (corpsRigide[1] && corpsRigide[1]->getMasse() < 100) {
		Vecteur3D newVitesse(corpsRigide[1]->getVitesse() + impulsePerIMass * (1.0f / corpsRigide[1]->getMasse()));
		corpsRigide[1]->setVitesse(newVitesse);
	}
}

float Contact::CalculateSeparatingVelocity() {
	Vecteur3D relativeVelocity = corpsRigide[0]->getVitesse();
	if (corpsRigide[1]) {
		relativeVelocity = corpsRigide[1]->getVitesse() - relativeVelocity;
	}
	return relativeVelocity.produitScalaire(contactNormal);
}

void Contact::Resolve(float duration) {
	ResolveVelocity(duration);
	ResolveInterpenetration();
}