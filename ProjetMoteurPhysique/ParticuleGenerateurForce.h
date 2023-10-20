#pragma once
#include "Particule.h"
class ParticuleGenerateurForce
{
public:
	virtual void MiseAJourForce(Particule* particule, double deltaTime);
};

