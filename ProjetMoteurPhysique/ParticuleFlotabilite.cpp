#include "ParticuleFlotabilite.h"

void ParticuleFlotabilite::MiseAJourForce(Particule* particule, double deltaTime) {

	//Calcule de d
	double d = (particule->getPosition().getY() - m_hauteurEau - m_profondeurMax) / (2 * m_profondeurMax);

	//On calcule la force en fonction du resultat de d
	double force;

	if (d <= 0) {
		force = 0;
	}
	else if (d >= 1) {
		force = m_volume * m_densiteLiquide;
	}
	else {
		force = d * m_volume * m_densiteLiquide;
	}

	//On applique la force
	particule->getAcceleration().setY(particule->getAcceleration().getY() * force / particule->getMasse() * deltaTime);

}