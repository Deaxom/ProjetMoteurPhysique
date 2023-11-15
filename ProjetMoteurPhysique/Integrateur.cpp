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

void Integrateur::MiseAJourCorpsRigide(CorpsRigide* corpsRigide, double* deltaTime)
{

	// mise a jour position
	corpsRigide->setPosition(corpsRigide->getPosition() + corpsRigide->getVitesse() * (*deltaTime));

	//mise a jour velocite
	corpsRigide->setVitesse(corpsRigide->getVitesse() + corpsRigide->getAcceleration() * (*deltaTime));

	//mise a jour de orientation
	Quaternion w(0, corpsRigide->getVelociteAngulaire().getX(), corpsRigide->getVelociteAngulaire().getY(), corpsRigide->getVelociteAngulaire().getZ());
	corpsRigide->setOrientation(corpsRigide->getOrientation() + w * corpsRigide->getOrientation() * (*(deltaTime) / 2));

	//mise a jour velocite angulaire
	Vecteur3D nouvelleVelociteAngulaire = corpsRigide->getVelociteAngulaire() + corpsRigide->getAccelerationAngulaire() * (*deltaTime);
	corpsRigide->SetVelociteAngulaire(nouvelleVelociteAngulaire);
	//orientation.UpdateByAngularVelocity(velociteAngulaire, deltaTime);

	corpsRigide->CalculerTranformationMatrice();
}
