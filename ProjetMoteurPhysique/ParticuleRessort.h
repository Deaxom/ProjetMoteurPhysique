#pragma once
#include "ParticuleGenerateurForce.h"
class ParticuleRessort : public ParticuleGenerateurForce
{
private:
	Particule* autreParticule;

	//Constante du ressort
	float m_k;
	float m_restLenght;
public:
	ParticuleRessort(Particule* autreParticule, float k, float restLenght);
	void MiseAJourForce(Particule* particule, double deltaTime);
};

