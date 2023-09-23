#include "Integrateur.h"
#include <iostream>



Vecteur3D Integrateur::UpdatePositionParticule(Particule particule, double deltaTime) {
	Vecteur3D newPosition = particule.getPosition() + (particule.getVitesse() * deltaTime);
	return newPosition;
}