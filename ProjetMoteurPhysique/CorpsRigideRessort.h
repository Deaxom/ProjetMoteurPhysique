#pragma once
#include "CorpsRigideGenerateurForce.h"
class CorpsRigideRessort : public CorpsRigideGenerateurForce
{
private:
	CorpsRigide* autreCorpsRigide;

	//Constante du ressort
	float m_k;
	float m_restLenght;
public:
	CorpsRigideRessort(CorpsRigide* autreCorpsRigide, float k, float restLenght);
	void MiseAJourForce(CorpsRigide* corpsRigide, double deltaTime);
};