#pragma once
#include "ParticuleGenerateurForce.h"
class ParticuleRessort : public ParticuleGenerateurForce
{
private:
	Particule* autreParticule;

	//Constante du ressort
	float m_k;
	// reste de la longueur
	float m_restLenght;

public:
	ParticuleRessort(Particule* _autreParticule, float k, float restLenght);
	void MiseAJourForce(Particule* particule, double deltaTime);
};

