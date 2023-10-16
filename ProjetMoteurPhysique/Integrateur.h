#pragma once
#include "Particule.h"

class Integrateur
{
public:
	Vecteur3D MiseAJourPositionParticule(Particule *particule, double *deltaTime);
	Vecteur3D MiseAJourVelociteParticule(Particule *particule, double *deltaTime);
};

