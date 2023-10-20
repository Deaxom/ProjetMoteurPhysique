#include "ParticuleRessort.h"

void ParticuleRessort::MiseAJourForce(Particule* particule, double deltaTime) {

	//calcule de la direction entre les deux particules
	Vecteur3D direction = autreParticule->getPosition() - particule->getPosition();

	//On calcule la norme pour avoir la distance
	double distance = direction.calculNorme();

	//calcul de la force via la loi de hooke	
	double force = m_k * (distance - m_restLenght);

	Vecteur3D vecteurForce = direction.calculVecteurUnitaire() * force;

	//On applique la force
	autreParticule->setAcceleration(autreParticule->getAcceleration().produitVectoriel(vecteurForce) * (1/autreParticule->getMasse()) * deltaTime);
	particule->setAcceleration(particule->getAcceleration().produitVectoriel(vecteurForce) * (1/particule->getMasse()) * deltaTime);
}