#pragma once
#include "Particule.h"
#include "ParticuleGenerateurForce.h"
#include <vector>

class ParticuleForceRegistre
{
private:
	struct ParticuleForceParametre
	{
		Particule* particule;
		ParticuleGenerateurForce *generateurForce;
	};

	using Registre = std::vector<ParticuleForceParametre>;
	Registre m_registre;

public:
	Registre getRegistre();
	void setRegiste(Registre nouveauRegistre);
	void addParticuleForceRegistre(Particule* particule, ParticuleGenerateurForce* generateurForce);
	void removeParticuleForceRegistre(Particule* particule, ParticuleGenerateurForce* generateurForce);

	// Clear toutes les génération d'accélérations de la frame
	void clear();

	void MiseAJourForce(double deltaTime);
};

