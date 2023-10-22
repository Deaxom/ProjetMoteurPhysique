#pragma once
#include "ParticuleGenerateurForce.h"

class ParticuleGravite : public ParticuleGenerateurForce
{
	// par défaut gravite terre (0.0, -9.81, 0.0)
	Vecteur3D gravity;

public:

	ParticuleGravite(const Vecteur3D& _gravity);

	void MiseAJourForce(Particule* particule, double deltaTime);
};

