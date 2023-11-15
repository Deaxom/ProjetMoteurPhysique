#include "CoprsRigide.h"

// Reprise des methodes de particule
//Constructeurs
CoprsRigide::CoprsRigide() {
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

CoprsRigide::CoprsRigide(Vecteur3D& position, const Vecteur3D& vitesse, const Vecteur3D& acceleration, double masse, Quaternion orientation, Vecteur3D velociteAngulaire, Vecteur3D accelerationAngulaire) {
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
Vecteur3D CoprsRigide::getPosition() {
	return this->position;
}

Vecteur3D CoprsRigide::getVitesse() const {
	return this->vitesse;
}

Vecteur3D CoprsRigide::getAcceleration() const {
	return this->acceleration;
}

double CoprsRigide::getMasse() {
	return this->masse;
}

Vecteur3D CoprsRigide::getLastVitesse() const
{
	return lastVitesse;
}

Quaternion CoprsRigide::getOrientation() const
{
	return orientation;
}

Vecteur3D CoprsRigide::getVelociteAngulaire() const
{
	return velociteAngulaire;
}

Vecteur3D CoprsRigide::getAccelerationAngulaire() const
{
	return accelerationAngulaire;
}

Matrix3x4 CoprsRigide::getTransmationMatrice() const
{
	return tranformationMatrice;
}

//SETTERS
void CoprsRigide::setPosition(Vecteur3D newPosition) {
	this->position = newPosition;
}

void CoprsRigide::setVitesse(Vecteur3D newVitesse) {
	this->vitesse = newVitesse;
}

void CoprsRigide::setAcceleration(Vecteur3D newAcceleration) {
	this->acceleration = acceleration + newAcceleration;

}void CoprsRigide::setMasse(double newMasse) {
	this->masse = newMasse;
}

void CoprsRigide::setLastVitesse(Vecteur3D _lastVitesse)
{
	this->lastVitesse = _lastVitesse;
}

void CoprsRigide::setOrientation(Quaternion& orientation)
{
	this->orientation = orientation;
}

void CoprsRigide::SetVelociteAngulaire(Vecteur3D& velociteAngulaire)
{
	this->velociteAngulaire = velociteAngulaire;
}

void CoprsRigide::SetAccelerationAngulaire(Vecteur3D& accelerationAngulaire)
{
	this->accelerationAngulaire = accelerationAngulaire;
}

void CoprsRigide::SetTransformationMatrice(Matrix3x4 transformationMatrice)
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

void CoprsRigide::CalculerTranformationMatrice()
{
	orientation.Normalized();

	tranformationMatrice.SetOrientationAndPos(orientation, position);
	
}

