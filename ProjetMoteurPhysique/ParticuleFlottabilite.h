#pragma once
#include "ParticuleGenerateurForce.h"
class ParticuleFlottabilite : public ParticuleGenerateurForce
{
private:

	//Constante de la flottabilite
	float m_profondeurMax;
	float m_volume;

	float m_hauteurEau;
	// Eau pure à 1000kg/m3
	float m_densiteLiquide;
public:
	ParticuleFlottabilite(float profondeur, float volume, float heuteurEau, float densiteLiquide = 1000.0f);

	void MiseAJourForce(Particule* particule, double deltaTime);
};

