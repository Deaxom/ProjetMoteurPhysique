#include "ParticuleFlottabilite.h"


ParticuleFlottabilite::ParticuleFlottabilite(float profondeurMax, float volume, float hauteurEau, float densiteLiquide) {
	this->m_profondeurMax = profondeurMax;
	this->m_volume = volume;
	this->m_hauteurEau = hauteurEau;
	this->m_densiteLiquide = densiteLiquide;
}

void ParticuleFlottabilite::MiseAJourForce(Particule* particule, double deltaTime) {

	//Calcule de d
	double d = (particule->getPosition().getY() - m_hauteurEau - m_profondeurMax) / (2 * (double)m_profondeurMax);

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
	Vecteur3D nouvelleAccelerationParticule(particule->getAcceleration().getX(), particule->getAcceleration().getY() * (force / particule->getMasse()) * deltaTime, particule->getAcceleration().getZ());
	particule->setAcceleration(nouvelleAccelerationParticule);

}