#include "ParticuleGravite.h"
#include "Constantes.h"

void ParticuleGravite::MiseAJourForce(Particule* particule, double deltaTime) {
	Vecteur3D nouvelleAccelerationParticule(particule->getAcceleration().getX(), -1 * particule->getMasse() * GRAVITATIONAL_CONSTANT * deltaTime, particule->getAcceleration().getZ());
	particule->setAcceleration(nouvelleAccelerationParticule);
}
