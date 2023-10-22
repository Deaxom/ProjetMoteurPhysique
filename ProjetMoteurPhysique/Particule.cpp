#include "Particule.h"

//Constructeurs
Particule::Particule() {
	Vecteur3D newPosition;
	Vecteur3D newVitesse;
	Vecteur3D newAcceleration;
	double masse = 0;
	forceAccum = Vecteur3D();
	this->setPosition(newPosition);
	this->setVitesse(newVitesse);
	this->setAcceleration(newAcceleration);
	this->setMasse(masse);
}

Particule::Particule(const Vecteur3D& position, const Vecteur3D& vitesse, const Vecteur3D& acceleration, double masse) {
	this->setPosition(position);
	this->setVitesse(vitesse);
	this->setAcceleration(acceleration);
	this->setMasse(masse);
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

Vecteur3D Particule::getForceAccum() const
{
	return this->forceAccum;
}

//SETTERS
void Particule::setPosition(Vecteur3D newPosition){
	this->position = newPosition;
}

void Particule::setVitesse(Vecteur3D newVitesse){
	this->vitesse = newVitesse;
}

void Particule::setAcceleration(Vecteur3D newAcceleration){
	this->acceleration = newAcceleration;

}void Particule::setMasse(double newMasse) {
	this->masse = newMasse;
}

void Particule::clearAccumulator()
{
	forceAccum = Vecteur3D();
}

void Particule::addForce(const Vecteur3D& force)
{
	forceAccum = forceAccum + force;
}

