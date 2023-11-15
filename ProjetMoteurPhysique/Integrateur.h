#pragma once
#include "Particule.h"
#include "CoprsRigide.h"

class Integrateur
{
public:
	void MiseAJourPositionParticule(Particule *particule, double *deltaTime);
	void MiseAJourVelociteParticule(Particule *particule, double *deltaTime);
	// Methode de modification position, orientation et velocite du coprs
	void MiseAJourCorpsRigide(CoprsRigide *coprsRigide, double *deltaTime);
};

