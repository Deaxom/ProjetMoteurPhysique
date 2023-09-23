#pragma once
#include "Particule.h"

class Integrateur
{
public:
	Vecteur3D UpdatePositionParticule(Particule particule, double deltaTime);
	double UpdateVelocityParticule(Particule particule);
};

