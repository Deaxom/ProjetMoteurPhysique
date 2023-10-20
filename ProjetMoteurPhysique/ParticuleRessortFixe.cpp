#include "ParticuleRessortFixe.h"

void ParticuleRessortFixe::MiseAJourForce(Particule* particule, double deltaTime) {

	//calcule de la direction entre les deux particules
	Vecteur3D direction = m_positionFixe - *particule->getPosition();

	//On calcule la norme pour avoir la distance
	double distance = direction.calculNorme();

	//calcul de la force via la loi de hooke	
	double force = m_k * (distance - m_restLenght);

	Vecteur3D vecteurForce = direction.calculVecteurUnitaire() * force;

	//On applique la force
	Vecteur3D resParticule = particule->getAcceleration()->produitVectoriel(vecteurForce) * (1 / particule->getMasse()) * deltaTime;
	particule->setAcceleration(&resParticule);
}
