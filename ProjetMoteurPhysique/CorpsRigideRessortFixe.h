#pragma once
#include "CorpsRigideGenerateurForce.h"
class CorpsRigideRessortFixe : public CorpsRigideGenerateurForce
{
private:
	Vecteur3D m_positionFixe;

	//Constante du ressort fixe
	float m_k;
	float m_restLenght;
public:
	CorpsRigideRessortFixe(Vecteur3D positionFixe, float k, float restLenght);
	void MiseAJourForce(CorpsRigide* corpsRigide, double deltaTime);
};