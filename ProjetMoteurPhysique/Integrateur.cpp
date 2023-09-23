#include "Integrateur.h"
#include <iostream>


Vecteur3D Integrateur::MiseAJourPositionParticule(Particule particule, double deltaTime) {
	Vecteur3D newPosition = particule.getPosition() + (particule.getVitesse() * deltaTime);
	return newPosition;
}

Vecteur3D Integrateur::MiseAJourVelociteParticule(Particule particule, double deltaTime) {
	Vecteur3D newVelocity = particule.getVitesse() * 0.8  + (particule.getAcceleration() * deltaTime);
	return newVelocity;
}