#pragma once
#include "ParticuleGenerateurForce.h"

class ParticuleGravite : public ParticuleGenerateurForce
{

	Vecteur3D gravity;

public:

	ParticuleGravite(const Vecteur3D& _gravity);

	void MiseAJourForce(Particule* particule, double deltaTime);
};

