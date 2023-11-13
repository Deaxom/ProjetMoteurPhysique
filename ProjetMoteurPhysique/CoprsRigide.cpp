#include "CoprsRigide.h"

// Reprise des methodes de particule
//Constructeurs
CoprsRigide::CoprsRigide() {
	Vecteur3D newPosition;
	Vecteur3D newVitesse;
	Vecteur3D newAcceleration;
	double masse = 0;
	this->setPosition(newPosition);
	this->setVitesse(newVitesse);
	this->setAcceleration(newAcceleration);
	this->setMasse(masse);
	this->setIsDynamic(false);
	this->setLastVitesse(getVitesse());
}

CoprsRigide::CoprsRigide(const Vecteur3D& position, const Vecteur3D& vitesse, const Vecteur3D& acceleration, double masse, bool isDynamic) {
	this->setPosition(position);
	this->setVitesse(vitesse);
	this->setAcceleration(acceleration);
	this->setMasse(masse);
	this->setIsDynamic(isDynamic);
	this->setLastVitesse(getVitesse());
}

//GETTERS
Vecteur3D CoprsRigide::getPosition() const {
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

bool CoprsRigide::getIsDynamic()
{
	return this->isDynamic;
}

Vecteur3D CoprsRigide::getLastVitesse() const
{
	return lastVitesse;
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

void CoprsRigide::setIsDynamic(bool _isDynamic)
{
	this->isDynamic = _isDynamic;
}

void CoprsRigide::setLastVitesse(Vecteur3D _lastVitesse)
{
	this->lastVitesse = _lastVitesse;
}

void CoprsRigide::MiseAJourCorps(double deltaTime)
{
	// mise a jour position
	position = position + vitesse * deltaTime;
	
	//mise a jour velocite
	vitesse = vitesse + acceleration * deltaTime;

	//mise a jour de orientation
	Quaternion w(0, velociteAngulaire.getX(), velociteAngulaire.getY(), velociteAngulaire.getZ());
	orientation = orientation +  w * orientation * (deltaTime / 2);

	//mise a jour velocite angulaire
	orientation.UpdateByAngularVelocity(velociteAngulaire, deltaTime);
}

void CoprsRigide::CalculerTranformationMatrice()
{

	orientation.Normalized();

	tranformationMatrice.SetOrientationAndPos(orientation, position);
	
}

