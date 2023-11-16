#pragma once
#include "CorpsRigide.h"
#include "CorpsRigideGenerateurForce.h"
#include <vector>

class CorpsRigideForceRegistre
{
private:
	struct CorpsRigideForceParametre
	{
		CorpsRigide* corpsRigide;
		CorpsRigideGenerateurForce* generateurForce;
	};

	using Registre = std::vector<CorpsRigideForceParametre>;
	Registre m_registre;

public:
	Registre getRegistre();
	void setRegiste(Registre nouveauRegistre);
	void addCorpsRigideForceRegistre(CorpsRigide* corpsRigide, CorpsRigideGenerateurForce* generateurForce);
	void removeCorpsRigideForceRegistre(CorpsRigide* corpsRigide, CorpsRigideGenerateurForce* generateurForce);

	// Clear toutes les génération d'accélérations de la frame
	void clear();

	void MiseAJourForce(double deltaTime);
};