#pragma once
#include "CorpsRigide.h"
class CorpsRigideGenerateurForce
{
public:
	virtual void MiseAJourForce(CorpsRigide* corpsRigide, double deltaTime);
};