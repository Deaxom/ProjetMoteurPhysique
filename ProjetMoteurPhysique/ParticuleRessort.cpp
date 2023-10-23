#include "ParticuleRessort.h"

ParticuleRessort::ParticuleRessort(Particule* _autreParticule, float k, float restLenght) :
	autreParticule(_autreParticule),
	m_k(k),
	m_restLenght(restLenght)
{
}

void ParticuleRessort::MiseAJourForce(Particule* particule, double deltaTime) {

	//calcule de la direction entre les deux particules
	Vecteur3D direction = autreParticule->getPosition() - particule->getPosition();

	//On calcule la norme pour avoir la distance
	double distance = direction.calculNorme();

	//calcul de la force via la loi de hooke	
	double force =  - 1 * m_k * (distance - m_restLenght);

	Vecteur3D vecteurForce = direction.calculVecteurUnitaire() * force;

	//On applique la force aux deux particules
	/*Vecteur3D newAccelerationAutreParticule(vecteurForce * (1 / autreParticule->getMasse()));
	autreParticule->setAcceleration(newAccelerationAutreParticule);

	Vecteur3D newAccelerationParticule(vecteurForce * (1 / particule->getMasse()));
	particule->setAcceleration(newAccelerationParticule);*/

	// obligation de creer deux registre dans cette situation pour applique une force a autreParticule
	particule->addForce(vecteurForce);

	// ne marche pas très probablement
	//autreParticule->addForce(vecteurForce);
}