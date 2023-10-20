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
}

Particule::Particule(Vecteur3D position, Vecteur3D vitesse, Vecteur3D acceleration, double masse) {
	this->setPosition(position);
	this->setVitesse(vitesse);
	this->setAcceleration(acceleration);
	this->setMasse(masse);
}

//GETTERS
Vecteur3D Particule::getPosition() {
	return this->position;
}

Vecteur3D Particule::getVitesse(){
	return this->vitesse;
}

Vecteur3D Particule::getAcceleration(){
	return this->acceleration;
}

double Particule::getMasse(){
	return this->masse;
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