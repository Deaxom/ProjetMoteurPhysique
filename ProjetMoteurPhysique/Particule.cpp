#include "Particule.h"

//Constructeurs
Particule::Particule() {
	Vecteur3D newPosition;
	Vecteur3D newVitesse;
	Vecteur3D newAcceleration;
	double masse = 0;
	this->setPosition(newPosition);
	this->setVitesse(newVitesse);
	this->setAcceleration(newAcceleration);
	this->setMasse(masse);
	this->setIsDynamic(true);
	this->setLastVitesse(getVitesse());
}

Particule::Particule(const Vecteur3D& position, const Vecteur3D& vitesse, const Vecteur3D& acceleration, double masse, bool isDynamic) {
	this->setPosition(position);
	this->setVitesse(vitesse);
	this->setAcceleration(acceleration);
	this->setMasse(masse);
	this->setIsDynamic(isDynamic);
	this->setLastVitesse(getVitesse());
}

//GETTERS
Vecteur3D Particule::getPosition() const {
	return this->position;
}

Vecteur3D Particule::getVitesse() const {
	return this->vitesse;
}

Vecteur3D Particule::getAcceleration() const {
	return this->acceleration;
}

double Particule::getMasse(){
	return this->masse;
}

bool Particule::getIsDynamic()
{
	return this->isDynamic;
}

Vecteur3D Particule::getLastVitesse() const
{
	return lastVitesse;
}

//SETTERS
void Particule::setPosition(Vecteur3D newPosition){
	this->position = newPosition;
}

void Particule::setVitesse(Vecteur3D newVitesse){
	this->vitesse = newVitesse;
}

void Particule::setAcceleration(Vecteur3D newAcceleration){
	this->acceleration = acceleration + newAcceleration;

}void Particule::setMasse(double newMasse) {
	this->masse = newMasse;
}

void Particule::setIsDynamic(bool _isDynamic)
{
	this->isDynamic = _isDynamic;
}

void Particule::setLastVitesse(Vecteur3D _lastVitesse)
{
	this->lastVitesse = _lastVitesse;
}
