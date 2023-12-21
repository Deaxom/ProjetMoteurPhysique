#pragma once
#include "Particule.h"
#include "CorpsRigide.h"

class Integrateur
{
public:
	void MiseAJourPositionParticule(Particule *particule, double *deltaTime);
	void MiseAJourVelociteParticule(Particule *particule, double *deltaTime);
	// Methode de modification position, orientation et velocite du corps
	void MiseAJourCorpsRigide(CorpsRigide *corpsRigide, double *deltaTime);

	void MiseAJourPositionCorpsRigide(CorpsRigide *corpsRigide, double *deltaTime);
	void MiseAJourForceCorpsRigide(CorpsRigide *corpsRigide, double *deltaTime);
	void MiseAJourVitesseCorpsRigide(CorpsRigide *corpsRigide, double *deltaTime);
};

