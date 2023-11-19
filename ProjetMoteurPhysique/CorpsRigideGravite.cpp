#include "CorpsRigideGravite.h"
#include "Constantes.h"

CorpsRigideGravite::CorpsRigideGravite(Vecteur3D gravity) :
	m_gravity(gravity)
{
}

CorpsRigideGravite::CorpsRigideGravite(float x, float y, float z) :
	m_gravity(Vecteur3D(x, y, z))
{
}

void CorpsRigideGravite::MiseAJourForce(CorpsRigide* corpsRigide, double deltaTime) {

	// Calcul de l'acc�l�ration due � la gravit� 
	Vecteur3D nouvelleAcceleration = m_gravity *  corpsRigide->getMasse();

	// Mettre � jour l'acc�l�ration du corps rigide
	corpsRigide->AjouterForce(nouvelleAcceleration);
}