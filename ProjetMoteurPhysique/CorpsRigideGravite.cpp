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
	//Calcul de la force de gravité (f=m*g avec g=G*m_terre/r^2)
	/*double distanceCorpsRigideTerre = corpsRigide->getPosition().calculNorme();
	double forceGravite = (GRAVITATIONAL_CONSTANT * corpsRigide->getMasse() * masseTerre) / (distanceCorpsRigideTerre * distanceCorpsRigideTerre);*/

	// Calcul de l'accélération due à la gravité (F=m*a donc a=F/m)
	float nouvelleAccelerationY = m_gracity.getY() / corpsRigide->getMasse();

	// Mettre à jour l'accélération du corps rigide
	Vecteur3D nouvelleAccelerationCorpsRigide(corpsRigide->getAcceleration().getX(), corpsRigide->getAcceleration().getY() + nouvelleAccelerationY, corpsRigide->getAcceleration().getZ());
	corpsRigide->setAcceleration(nouvelleAccelerationCorpsRigide);
}