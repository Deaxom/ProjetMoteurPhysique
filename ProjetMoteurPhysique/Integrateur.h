#pragma once
#include "Particule.h"

class Integrateur
{
public:
	void MiseAJourPositionParticule(Particule *particule, float deltaTime);
	void MiseAJourVelociteParticule(Particule *particule, float deltaTime);
};

