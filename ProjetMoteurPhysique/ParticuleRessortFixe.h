#pragma once
#include "ParticuleGenerateurForce.h"
class ParticuleRessortFixe : public ParticuleGenerateurForce
{
private:
	Vecteur3D m_positionFixe;

	//Constante du ressort fixe
	float m_k;
	float m_restLenght;
public:
	ParticuleRessortFixe(Vecteur3D positionFixe);
	void MiseAJourForce(Particule* particule, double deltaTime);
};

