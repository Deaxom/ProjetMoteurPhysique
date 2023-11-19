#pragma once
#include "ParticuleGenerateurForce.h"
class ParticuleGravite : public ParticuleGenerateurForce
{
private:
	Vecteur3D m_gravity;

public:
	ParticuleGravite(Vecteur3D gravity);
	ParticuleGravite(float x, float y, float z);
	void MiseAJourForce(Particule* particule, double deltaTime);
};