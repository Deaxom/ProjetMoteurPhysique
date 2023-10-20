#pragma once
#include "ParticuleGenerateurForce.h"
class ParticuleFlotabilite : public ParticuleGenerateurForce
{
private:

	//Constante de la flotabilite
	float m_profondeurMax;
	float m_volume;

	float m_hauteurEau;
	float m_densiteLiquide;
public:
	void MiseAJourForce(Particule* particule, double deltaTime);
};

