#include "Integrateur.h"
#include <iostream>
#include "Constantes.h"


void Integrateur::MiseAJourPositionParticule(Particule *particule, double *deltaTime) {
    Vecteur3D newPosition = (particule->getPosition()) + (particule->getVitesse()) * (*deltaTime);
    Vecteur3D newPositionPtr(newPosition);
    
    particule->setPosition(newPositionPtr);
}

void Integrateur::MiseAJourVelociteParticule(Particule *particule, double *deltaTime) {
	Vecteur3D newVelocity = (particule->getVitesse()) * DAMPING_VALUE + ((particule->getAcceleration()) * (*deltaTime));
    Vecteur3D newVelocityPtr(newVelocity);


    particule->setAcceleration(particule->getAcceleration() * -1);
    particule->setLastVitesse(particule->getVitesse());
    particule->setVitesse(newVelocityPtr);
}

void Integrateur::MiseAJourCorpsRigide(CoprsRigide* coprsRigide, double* deltaTime)
{

	// mise a jour position
	coprsRigide->setPosition(coprsRigide->getPosition() + coprsRigide->getVitesse() * (*deltaTime));

	//mise a jour velocite
	coprsRigide->setVitesse(coprsRigide->getVitesse() + coprsRigide->getAcceleration() * (*deltaTime));

	//mise a jour de orientation
	Quaternion w(0, coprsRigide->getVelociteAngulaire().getX(), coprsRigide->getVelociteAngulaire().getY(), coprsRigide->getVelociteAngulaire().getZ());
	coprsRigide->setOrientation(coprsRigide->getOrientation() + w * coprsRigide->getOrientation() * (*(deltaTime) / 2));

	//mise a jour velocite angulaire
	Vecteur3D nouvelleVelociteAngulaire = coprsRigide->getVelociteAngulaire() + coprsRigide->getAccelerationAngulaire() * (*deltaTime);
	coprsRigide->SetVelociteAngulaire(nouvelleVelociteAngulaire);
	//orientation.UpdateByAngularVelocity(velociteAngulaire, deltaTime);

	coprsRigide->CalculerTranformationMatrice();
}
