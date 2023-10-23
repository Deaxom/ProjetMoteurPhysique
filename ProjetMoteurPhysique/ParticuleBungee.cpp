#include "ParticuleBungee.h"

ParticuleBungee::ParticuleBungee(Particule* m_other, float k, float restLength) :
	other(m_other),
	m_k(k),
	m_restLength(restLength)
{
}

void ParticuleBungee::MiseAJourForce(Particule* particule, float duration)
{
	//calcule de la direction entre les deux particules
	Vecteur3D direction = other->getPosition() - particule->getPosition();

	//On calcule la norme pour avoir la distance
	float distance = direction.calculNorme();
	
	//Arrete si l'objet essaye de s'approcher
	if (distance <= m_restLength) return;

	//calcul de la force via la loi de hooke	
	float force = m_k * (m_restLength - distance);

	Vecteur3D vecteurForce = direction.calculVecteurUnitaire() * force * -1.f;

	particule->addForce(vecteurForce);
}
