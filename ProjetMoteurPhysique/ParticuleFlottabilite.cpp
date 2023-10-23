#include "ParticuleFlottabilite.h"



ParticuleFlottabilite::ParticuleFlottabilite(float profondeur, float volume, float heuteurEau, float densiteLiquide):
	m_profondeurMax(profondeur),
	m_volume(volume),
	m_hauteurEau(heuteurEau),
	m_densiteLiquide(densiteLiquide)
{
}

void ParticuleFlottabilite::MiseAJourForce(Particule* particule, double deltaTime) {

	//Calcule de d
	float d = (particule->getPosition().getY() - m_hauteurEau - m_profondeurMax) / (2 * m_profondeurMax);
	
	// Check hauteur de la particule
	//float d = particule->getPosition().getY();
	// Check si il n'est pas dans l'eau
	if (d <= 0) return;

	//On calcule la force en fonction du resultat de d
	//double force;
	Vecteur3D force(0, 0, 0);

	/*if (d <= 0) {
		force = 0;
	}
	else if (d >= 1) {
		force = (double)m_volume * m_densiteLiquide;
	}
	else {
		force = d * m_volume * m_densiteLiquide;
	}*/

	if (d >= 1) {
		force = Vecteur3D(0, m_volume * m_densiteLiquide, 0);
		particule->addForce(force);
		return;
	}

	force = Vecteur3D(0, force.getY() * (1 / particule->getMasse()), 0);
	particule->addForce(force);


	//On applique la force
	/*Vecteur3D nouvelleAccelerationParticule(particule->getAcceleration().getX(), particule->getAcceleration().getY() * (force / particule->getMasse()) * deltaTime, particule->getAcceleration().getZ());
	particule->setAcceleration(nouvelleAccelerationParticule);*/

}