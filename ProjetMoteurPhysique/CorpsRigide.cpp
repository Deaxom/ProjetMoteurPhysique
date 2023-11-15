#include "CorpsRigide.h"

// Reprise des methodes de particule
//Constructeurs
CorpsRigide::CorpsRigide() {
	Vecteur3D newPosition;
	Vecteur3D newVitesse;
	Vecteur3D newAcceleration;
	double masse = 0;
	Quaternion newOrientation;
	Vecteur3D newVelociteAngulaire;
	Vecteur3D newAccelerationAngulaire;
	this->setPosition(newPosition);
	this->setVitesse(newVitesse);
	this->setAcceleration(newAcceleration);
	this->setMasse(masse);
	this->setLastVitesse(getVitesse());
	this->setOrientation(newOrientation);
	this->SetVelociteAngulaire(newVelociteAngulaire);
	this->SetAccelerationAngulaire(newAccelerationAngulaire);
	Matrix3x4 newMatrice;
	newMatrice.SetOrientationAndPos(newOrientation, newPosition);
	this->SetTransformationMatrice(newMatrice);
	
}

CorpsRigide::CorpsRigide(Vecteur3D& position, const Vecteur3D& vitesse, const Vecteur3D& acceleration, double masse, Quaternion orientation, Vecteur3D velociteAngulaire, Vecteur3D accelerationAngulaire) {
	this->setPosition(position);
	this->setVitesse(vitesse);
	this->setAcceleration(acceleration);
	this->setMasse(masse);
	this->setLastVitesse(getVitesse());
	this->setOrientation(orientation);
	this->SetVelociteAngulaire(velociteAngulaire);
	this->SetAccelerationAngulaire(accelerationAngulaire);
	Matrix3x4 newMatrice;
	newMatrice.SetOrientationAndPos(orientation, position);
	this->SetTransformationMatrice(newMatrice);
}

//GETTERS
Vecteur3D CorpsRigide::getPosition() {
	return this->position;
}

Vecteur3D CorpsRigide::getVitesse() const {
	return this->vitesse;
}

Vecteur3D CorpsRigide::getAcceleration() const {
	return this->acceleration;
}

double CorpsRigide::getMasse() {
	return this->masse;
}

Vecteur3D CorpsRigide::getLastVitesse() const
{
	return lastVitesse;
}

Quaternion CorpsRigide::getOrientation() const
{
	return orientation;
}

Vecteur3D CorpsRigide::getVelociteAngulaire() const
{
	return velociteAngulaire;
}

Vecteur3D CorpsRigide::getAccelerationAngulaire() const
{
	return accelerationAngulaire;
}

Matrix3x4 CorpsRigide::getTransmationMatrice() const
{
	return tranformationMatrice;
}

//SETTERS
void CorpsRigide::setPosition(Vecteur3D newPosition) {
	this->position = newPosition;
}

void CorpsRigide::setVitesse(Vecteur3D newVitesse) {
	this->vitesse = newVitesse;
}

void CorpsRigide::setAcceleration(Vecteur3D newAcceleration) {
	this->acceleration = acceleration + newAcceleration;

}void CorpsRigide::setMasse(double newMasse) {
	this->masse = newMasse;
}

void CorpsRigide::setLastVitesse(Vecteur3D _lastVitesse)
{
	this->lastVitesse = _lastVitesse;
}

void CorpsRigide::setOrientation(Quaternion& orientation)
{
	this->orientation = orientation;
}

void CorpsRigide::SetVelociteAngulaire(Vecteur3D& velociteAngulaire)
{
	this->velociteAngulaire = velociteAngulaire;
}

void CorpsRigide::SetAccelerationAngulaire(Vecteur3D& accelerationAngulaire)
{
	this->accelerationAngulaire = accelerationAngulaire;
}

void CorpsRigide::SetTransformationMatrice(Matrix3x4 transformationMatrice)
{
	this->tranformationMatrice = transformationMatrice;
}

//void CoprsRigide::MiseAJourCorps(double &deltaTime)
//{
//	// mise a jour position
//	position = position + vitesse * deltaTime;
//	
//	//mise a jour velocite
//	vitesse = vitesse + acceleration * deltaTime;
//
//	//mise a jour de orientation
//	Quaternion w(0, velociteAngulaire.getX(), velociteAngulaire.getY(), velociteAngulaire.getZ());
//	orientation = orientation +  w * orientation * (deltaTime / 2);
//
//	//mise a jour velocite angulaire
//	velociteAngulaire = velociteAngulaire + accelerationAngulaire * deltaTime;
//	//orientation.UpdateByAngularVelocity(velociteAngulaire, deltaTime);
//
//	CalculerTranformationMatrice();
//}

void CorpsRigide::CalculerTranformationMatrice()
{
	orientation.Normalized();

	tranformationMatrice.SetOrientationAndPos(orientation, position);
	
}

