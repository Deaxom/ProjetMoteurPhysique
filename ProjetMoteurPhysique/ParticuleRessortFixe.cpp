#include "ParticuleRessortFixe.h"

ParticuleRessortFixe::ParticuleRessortFixe(Vecteur3D positionFixe) {
	this->m_positionFixe = positionFixe;
}

void ParticuleRessortFixe::MiseAJourForce(Particule* particule, double deltaTime) {

	//calcule de la direction entre les deux particules
	Vecteur3D direction = m_positionFixe - *particule->getPosition();

	//On calcule la norme pour avoir la distance
	double distance = direction.calculNorme();

	//calcul de la force via la loi de hooke	
	double force = -1 * m_k * (distance - m_restLenght);

	Vecteur3D vecteurForce = direction.calculVecteurUnitaire() * force;

	//On applique la force
	Vecteur3D* newAccelerationParticule = new Vecteur3D(vecteurForce * (1 / particule->getMasse())); // *deltaTime;
	particule->setAcceleration(newAccelerationParticule);
}
