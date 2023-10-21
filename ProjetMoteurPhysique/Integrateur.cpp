#include "Integrateur.h"
#include <iostream>
#include "Constantes.h"


void Integrateur::MiseAJourPositionParticule(Particule *particule, double *deltaTime) {
    Vecteur3D newPosition = (*particule->getPosition()) + (*particule->getVitesse()) * (*deltaTime);
    Vecteur3D* newPositionPtr = new Vecteur3D(newPosition);
    
    particule->setPosition(newPositionPtr);
}

void Integrateur::MiseAJourVelociteParticule(Particule *particule, double *deltaTime) {
	Vecteur3D newVelocity = (*particule->getVitesse()) * DAMPING_VALUE + ((*particule->getAcceleration()) * (*deltaTime));
    Vecteur3D* newVelocityPtr = new Vecteur3D(newVelocity);

    particule->setVitesse(newVelocityPtr);
}