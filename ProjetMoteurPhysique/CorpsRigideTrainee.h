#pragma once
#include "CorpsRigideGenerateurForce.h"
class CorpsRigideTrainee : public CorpsRigideGenerateurForce
{
private:
	float m_k1;
	float m_k2;
public:
	CorpsRigideTrainee(float k1, float k2);

	void MiseAJourForce(CorpsRigide* corpsRigide, double deltaTime);
};