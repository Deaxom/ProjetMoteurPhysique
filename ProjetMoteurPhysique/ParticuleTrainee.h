#pragma once
#include "ParticuleGenerateurForce.h"
class ParticuleTrainee : public ParticuleGenerateurForce
{
private:
	float m_k1;
	float m_k2;
public:
	void MiseAJourForce(Particule* particule, double deltaTime);
};

