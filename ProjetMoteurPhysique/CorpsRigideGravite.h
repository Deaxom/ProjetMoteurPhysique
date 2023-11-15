#pragma once
#include "CorpsRigideGenerateurForce.h"
class CorpsRigideGravite : public CorpsRigideGenerateurForce
{
private:
	Vecteur3D m_gracity;

public:
	CorpsRigideGravite(Vecteur3D gravity);
	CorpsRigideGravite(float x, float y, float z);
	void MiseAJourForce(CorpsRigide* corpsRigide, double deltaTime);
};