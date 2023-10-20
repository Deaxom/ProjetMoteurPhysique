#pragma once
#include "ParticuleGenerateurForce.h"
class ParticuleGravite : public ParticuleGenerateurForce
{
public:
	void MiseAJourForce(Particule* particule, double deltaTime);
};

