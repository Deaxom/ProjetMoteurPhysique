#include "CorpsRigideRessort.h"

CorpsRigideRessort::CorpsRigideRessort(CorpsRigide* autreCorpsRigide, float k, float restLenght) {
	this->autreCorpsRigide = autreCorpsRigide;
	this->m_k = k;
	this->m_restLenght = restLenght;
}

void CorpsRigideRessort::MiseAJourForce(CorpsRigide* corpsRigide, double deltaTime) {

	//calcule de la direction entre les deux corps rigides
	Vecteur3D direction = autreCorpsRigide->getPosition() - corpsRigide->getPosition();


	//On calcule la norme pour avoir la distance
	double distance = direction.calculNorme();

	//calcul de la force via la loi de hooke	
	double force = -1 * m_k * (distance - m_restLenght);

	Vecteur3D vecteurForce = direction.calculVecteurUnitaire() * force;

	//On applique la force aux deux corps rigides
	autreCorpsRigide->AjouterForce(vecteurForce * -1);
	corpsRigide->AjouterForce(vecteurForce);
}