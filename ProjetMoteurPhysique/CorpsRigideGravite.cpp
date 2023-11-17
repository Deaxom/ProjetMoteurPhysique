#include "CorpsRigideGravite.h"
#include "Constantes.h"

CorpsRigideGravite::CorpsRigideGravite(Vecteur3D gravity) :
	m_gracity(gravity)
{
}

CorpsRigideGravite::CorpsRigideGravite(float x, float y, float z) :
	m_gracity(Vecteur3D(x, y, z))
{
}

void CorpsRigideGravite::MiseAJourForce(CorpsRigide* corpsRigide, double deltaTime) {

	// Calcul de l'accélération due à la gravité 
	Vecteur3D nouvelleAcceleration = m_gracity *  corpsRigide->getMasse();

	// Mettre à jour l'accélération du corps rigide
	corpsRigide->AjouterForce(nouvelleAcceleration);
}