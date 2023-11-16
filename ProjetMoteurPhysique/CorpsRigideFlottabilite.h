#pragma once
#include "CorpsRigideGenerateurForce.h"
class CorpsRigideFlottabilite : public CorpsRigideGenerateurForce
{
private:
	//Constante de la flottabilite
	float m_profondeurMax;
	float m_volume;

	float m_hauteurEau;
	float m_densiteLiquide;
public:
	CorpsRigideFlottabilite(float profondeurMax, float volume, float hauteurEau, float densiteLiquide);
	void MiseAJourForce(CorpsRigide* corpsRigide, double deltaTime);
};