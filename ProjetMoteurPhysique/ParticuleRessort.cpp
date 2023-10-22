#include "ParticuleRessort.h"

ParticuleRessort::ParticuleRessort(Particule* autreParticule) {
	this->autreParticule = autreParticule;
}

void ParticuleRessort::MiseAJourForce(Particule* particule, double deltaTime) {

	//calcule de la direction entre les deux particules
	Vecteur3D direction = *autreParticule->getPosition() - *particule->getPosition();


	//On calcule la norme pour avoir la distance
	double distance = direction.calculNorme();

	//calcul de la force via la loi de hooke	
	double force =  - 1 * m_k * (distance - m_restLenght);

	Vecteur3D vecteurForce = direction.calculVecteurUnitaire() * force;

	//On applique la force aux deux particules
	Vecteur3D* newAccelerationAutreParticule = new Vecteur3D(vecteurForce * (1 / autreParticule->getMasse()));// *deltaTime;
	autreParticule->setAcceleration(newAccelerationAutreParticule);

	Vecteur3D* newAccelerationParticule = new Vecteur3D(vecteurForce * (1 / particule->getMasse()));// *deltaTime;
	particule->setAcceleration(newAccelerationParticule);
}