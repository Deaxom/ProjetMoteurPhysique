#include "Integrateur.h"
#include <iostream>
#include "Constantes.h"


void Integrateur::MiseAJourPositionParticule(Particule *particule, float deltaTime) {
    Vecteur3D newPosition = (particule->getPosition()) + (particule->getVitesse()) * deltaTime;
    Vecteur3D newPositionPtr(newPosition);
    
    particule->setPosition(newPositionPtr);
}

void Integrateur::MiseAJourVelociteParticule(Particule *particule, float deltaTime) {
    Vecteur3D resultingAcc = particule->getAcceleration();
    particule->clearAccumulator();
    resultingAcc = resultingAcc + (particule->getForceAccum() * (1.0f / particule->getMasse()));
	Vecteur3D newVelocity = (particule->getVitesse()) * DAMPING_VALUE + (resultingAcc * deltaTime);

    particule->setVitesse(newVelocity);
}