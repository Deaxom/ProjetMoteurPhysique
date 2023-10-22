#include "ParticuleGravite.h"
#include "Constantes.h"

ParticuleGravite::ParticuleGravite(const Vecteur3D& _gravity) :
	gravity(_gravity)
{
}

void ParticuleGravite::MiseAJourForce(Particule* particule, double deltaTime) {
	//Calcul de la force de gravit� (f=m*g avec g=G*m_terre/r^2)
	double distanceParticuleTerre = particule->getPosition().calculNorme();
	double forceGravite = (GRAVITATIONAL_CONSTANT * particule->getMasse() * masseTerre) / (distanceParticuleTerre * distanceParticuleTerre);

	//// Calcul de l'acc�l�ration due � la gravit� (F=m*a donc a=F/m)
	//double nouvelleAccelerationY = forceGravite / particule->getMasse();

	// Mettre � jour l'acc�l�ration de la particule
	Vecteur3D nouvelleAccelerationParticule(particule->getAcceleration().getX(), - nouvelleAccelerationY, particule->getAcceleration().getZ());
	particule->setAcceleration(nouvelleAccelerationParticule);

	float masseParticule = particule->getMasse();
	float distance = particule->getPosition()->calculNorme();
	Vecteur3D forceGravitationnel = gravity * (masseParticule / (distance * distance));
}
