#include "ParticuleRessortFixe.h"

ParticuleRessortFixe::ParticuleRessortFixe(Vecteur3D positionFixe, float k, float restLenght) {
	this->m_positionFixe = positionFixe;
	this->m_k = k;
	this->m_restLenght = restLenght;
}

void ParticuleRessortFixe::MiseAJourForce(Particule* particule, double deltaTime) {

	//calcule de la direction entre les deux particules
	Vecteur3D direction = m_positionFixe - particule->getPosition();

	//On calcule la norme pour avoir la distance
	double distance = direction.calculNorme();

	//calcul de la force via la loi de hooke	
	double force = -1 * m_k * (distance - m_restLenght);

	Vecteur3D vecteurForce = direction.calculVecteurUnitaire() * force;

	//On applique la force
	Vecteur3D newAccelerationParticule(vecteurForce * (1 / particule->getMasse()));
	particule->setAcceleration(newAccelerationParticule);
}