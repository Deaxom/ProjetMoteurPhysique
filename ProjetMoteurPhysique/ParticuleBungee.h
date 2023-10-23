#pragma once
#include "ParticuleGenerateurForce.h"

class ParticuleBungee : public ParticuleGenerateurForce
{
private:
	Particule* other;
	float m_k;
	float m_restLength;

public:
	ParticuleBungee(Particule* m_other, float k, float restLength);

	void MiseAJourForce(Particule* particule, float duration);
};
