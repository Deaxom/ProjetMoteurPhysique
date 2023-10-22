#include "ParticuleGravite.h"
#include "Constantes.h"

void ParticuleGravite::MiseAJourForce(Particule* particule, double deltaTime) {
	//Calcul de la force de gravité (f=m*g avec g=G*m_terre/r^2)
	double distanceParticuleTerre = particule->getPosition()->calculNorme();
	double forceGravite = (GRAVITATIONAL_CONSTANT * particule->getMasse() * masseTerre) / (distanceParticuleTerre * distanceParticuleTerre);

	// Calcul de l'accélération due à la gravité (F=m*a donc a=F/m)
	double nouvelleAccelerationY = forceGravite / particule->getMasse();

	// Mettre à jour l'accélération de la particule
	Vecteur3D* nouvelleAccelerationParticule = new Vecteur3D(particule->getAcceleration()->getX(), - nouvelleAccelerationY, particule->getAcceleration()->getZ());
	particule->setAcceleration(nouvelleAccelerationParticule);
}
