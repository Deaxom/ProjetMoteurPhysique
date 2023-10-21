#pragma once
#include "Particule.h"

class Integrateur
{
public:
	void MiseAJourPositionParticule(Particule *particule, double *deltaTime);
	void MiseAJourVelociteParticule(Particule *particule, double *deltaTime);
};

