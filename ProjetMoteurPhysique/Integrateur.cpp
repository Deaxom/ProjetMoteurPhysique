#include "Integrateur.h"
#include <iostream>
#include "Constantes.h"


Vecteur3D* Integrateur::MiseAJourPositionParticule(Particule *particule, double *deltaTime) {
	//double deltaTime = 1;
	//Vecteur3D newPosition = particule->getPosition() + (particule->getVitesse() * (*deltaTime));
	//return newPosition;
	return new Vecteur3D(1,1,1);
}

Vecteur3D* Integrateur::MiseAJourVelociteParticule(Particule *particule, double *deltaTime) {
	//double deltaTime = 1;
	//Vecteur3D newVelocity = particule->getVitesse() * DAMPING_VALUE + (particule->getAcceleration() * (*deltaTime));
	//return newVelocity;
	return new Vecteur3D(1, 1, 1);
}