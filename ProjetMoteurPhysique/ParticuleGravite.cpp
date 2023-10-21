#include "ParticuleGravite.h"
#include "Constantes.h"

void ParticuleGravite::MiseAJourForce(Particule* particule, double deltaTime) {
	double nouveauY = -1 * particule->getMasse() * GRAVITATIONAL_CONSTANT * deltaTime;
	Vecteur3D* nouvelleAccelerationParticule = new Vecteur3D(particule->getAcceleration()->getX(), nouveauY, particule->getAcceleration()->getZ());
	particule->setAcceleration(nouvelleAccelerationParticule);
}
