#include "ParticuleGravite.h"
#include "Constantes.h"

ParticuleGravite::ParticuleGravite(Vecteur3D gravity) :
	m_gravity(gravity)
{
}

ParticuleGravite::ParticuleGravite(float x, float y, float z) :
	m_gravity(Vecteur3D(x, y, z))
{
}

void ParticuleGravite::MiseAJourForce(Particule* particule, double deltaTime) {
	//Calcul de la force de gravité (f=m*g avec g=G*m_terre/r^2)
	/*double distanceParticuleTerre = particule->getPosition().calculNorme();
	double forceGravite = (GRAVITATIONAL_CONSTANT * particule->getMasse() * masseTerre) / (distanceParticuleTerre * distanceParticuleTerre);*/

	// Calcul de l'accélération due à la gravité (F=m*a donc a=F/m)
	float nouvelleAccelerationY = m_gravity.getY() / particule->getMasse();

	// Mettre à jour l'accélération de la particule
	Vecteur3D nouvelleAccelerationParticule(particule->getAcceleration().getX(), particule->getAcceleration().getY() + nouvelleAccelerationY, particule->getAcceleration().getZ());
	particule->setAcceleration(nouvelleAccelerationParticule);
}