#pragma once
#include "ParticuleGenerateurForce.h"
class ParticuleFlottabilite : public ParticuleGenerateurForce
{
private:

	//Constante de la flottabilite
	float m_profondeurMax;
	float m_volume;

	float m_hauteurEau;
	float m_densiteLiquide;
public:
	ParticuleFlottabilite(float profondeurMax, float volume, float hauteurEau, float densiteLiquide);
	void MiseAJourForce(Particule* particule, double deltaTime);
};

