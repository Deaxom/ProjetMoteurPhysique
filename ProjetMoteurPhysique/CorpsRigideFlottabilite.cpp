#include "CorpsRigideFlottabilite.h"

CorpsRigideFlottabilite::CorpsRigideFlottabilite(float profondeurMax, float volume, float hauteurEau, float densiteLiquide) {
	this->m_profondeurMax = profondeurMax;
	this->m_volume = volume;
	this->m_hauteurEau = hauteurEau;
	this->m_densiteLiquide = densiteLiquide;
}

void CorpsRigideFlottabilite::MiseAJourForce(CorpsRigide* corpsRigide, double deltaTime) {

	//Calcule de d
	double d = (corpsRigide->getPosition().getY() - m_hauteurEau - m_profondeurMax) / (2 * (double)m_profondeurMax);

	//On calcule la force en fonction du resultat de d
	double force;

	if (d <= 0) {
		force = 0;
	}
	else if (d >= 1) {
		force = (double)m_volume * m_densiteLiquide;
	}
	else {
		force = d * m_volume * m_densiteLiquide;
	}

	//On applique la force
	float nouvelleAcceleration = force * (1 / corpsRigide->getMasse());
	Vecteur3D nouvelleAccelerationCorpsRigide(corpsRigide->getAcceleration().getX(), nouvelleAcceleration, corpsRigide->getAcceleration().getZ());
	//Vecteur3D nouvelleAccelerationParticule(corpsRigide->getAcceleration().getX(), corpsRigide->getAcceleration().getY() * (force / corpsRigide->getMasse()) * deltaTime, corpsRigide->getAcceleration().getZ());
	corpsRigide->setAcceleration(nouvelleAccelerationCorpsRigide);
}