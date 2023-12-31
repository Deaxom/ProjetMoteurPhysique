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


	//mise a jour de orientation
	Quaternion w(0, corpsRigide->getVelociteAngulaire().getX(), corpsRigide->getVelociteAngulaire().getY(), corpsRigide->getVelociteAngulaire().getZ());
	corpsRigide->setOrientation(corpsRigide->getOrientation() + w * corpsRigide->getOrientation() * (*(deltaTime) / 2));

	corpsRigide->CalculerTransformationMatrice();

	//mise a jour acceleration
	Vecteur3D nouvelleAcceleration = corpsRigide->getForceAccumulateur() * (1 / corpsRigide->getMasse());
	corpsRigide->setAcceleration(nouvelleAcceleration);

	
	//On transforme le quaternion orientation en matrice 
	Matrix3x3 matriceRotation = corpsRigide->getOrientation().TransformerEnMatriceRotation();

	// On change la base du tenseur intertie local dans le monde
	Matrix3x3 tenseurInertieInverseMonde = matriceRotation * corpsRigide->getTenseurInertieInverse() * matriceRotation.Inverse();

	//mise a jour acceleration angulaire
	Vecteur3D nouvelleAccelerationAngulaire = corpsRigide->getAccelerationAngulaire() + tenseurInertieInverseMonde * corpsRigide->getTorqueAccumulateur();
	corpsRigide->SetAccelerationAngulaire(nouvelleAccelerationAngulaire);

	//mise a jour velocite
	corpsRigide->setVitesse(corpsRigide->getVitesse() + corpsRigide->getAcceleration() * (*deltaTime));


	//mise a jour velocite angulaire
	Vecteur3D nouvelleVelociteAngulaire = corpsRigide->getVelociteAngulaire() + corpsRigide->getAccelerationAngulaire() * (*deltaTime);
	corpsRigide->SetVelociteAngulaire(nouvelleVelociteAngulaire);


	corpsRigide->NettoyerAccumulateur();
}

void Integrateur::MiseAJourPositionCorpsRigide(CorpsRigide* corpsRigide, double* deltaTime)
{
	// mise a jour position
	corpsRigide->setPosition(corpsRigide->getPosition() + corpsRigide->getVitesse() * (*deltaTime));
	
	//mise a jour de orientation
	Quaternion w(0, corpsRigide->getVelociteAngulaire().getX(), corpsRigide->getVelociteAngulaire().getY(), corpsRigide->getVelociteAngulaire().getZ());
	corpsRigide->setOrientation(corpsRigide->getOrientation() + w * corpsRigide->getOrientation() * (*(deltaTime) / 2));

	corpsRigide->CalculerTransformationMatrice();
}

void Integrateur::MiseAJourForceCorpsRigide(CorpsRigide* corpsRigide, double* deltaTime)
{
	//mise a jour acceleration
	Vecteur3D nouvelleAcceleration = corpsRigide->getForceAccumulateur() * (1 / corpsRigide->getMasse());
	corpsRigide->setAcceleration(nouvelleAcceleration);

	
	//On transforme le quaternion orientation en matrice 
	Matrix3x3 matriceRotation = corpsRigide->getOrientation().TransformerEnMatriceRotation();

	// On change la base du tenseur intertie local dans le monde
	Matrix3x3 tenseurInertieInverseMonde = matriceRotation * corpsRigide->getTenseurInertieInverse() * matriceRotation.Inverse();

	//mise a jour acceleration angulaire
	Vecteur3D nouvelleAccelerationAngulaire = corpsRigide->getAccelerationAngulaire() + tenseurInertieInverseMonde * corpsRigide->getTorqueAccumulateur();
	corpsRigide->SetAccelerationAngulaire(nouvelleAccelerationAngulaire);
}

void Integrateur::MiseAJourVitesseCorpsRigide(CorpsRigide* corpsRigide, double* deltaTime)
{
	//mise a jour velocite
	corpsRigide->setVitesse(corpsRigide->getVitesse() + corpsRigide->getAcceleration() * (*deltaTime));


	//mise a jour velocite angulaire
	Vecteur3D nouvelleVelociteAngulaire = corpsRigide->getVelociteAngulaire() + corpsRigide->getAccelerationAngulaire() * (*deltaTime);
	corpsRigide->SetVelociteAngulaire(nouvelleVelociteAngulaire);


	corpsRigide->NettoyerAccumulateur();
}
