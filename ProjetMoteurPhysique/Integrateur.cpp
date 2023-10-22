#include "Integrateur.h"
#include <iostream>
#include "Constantes.h"


void Integrateur::MiseAJourPositionParticule(Particule *particule, double *deltaTime) {
    Vecteur3D newPosition = (particule->getPosition()) + (particule->getVitesse()) * (*deltaTime);
    Vecteur3D newPositionPtr(newPosition);
    
    particule->setPosition(newPositionPtr);
}

void Integrateur::MiseAJourVelociteParticule(Particule *particule, double *deltaTime) {
    Vecteur3D resultingAcc = particule->getAcceleration();
    resultingAcc = resultingAcc + (particule->getForceAccum() * (1.0f / particule->getMasse()));
    particule->clearAccumulator();
	Vecteur3D newVelocity = (particule->getVitesse()) * DAMPING_VALUE + (resultingAcc * (*deltaTime));
    Vecteur3D newVelocityPtr(newVelocity);

    particule->setVitesse(newVelocityPtr);
}