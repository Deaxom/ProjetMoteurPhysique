#include "Particule.h"

//Constructeurs
Particule::Particule() {
	Vecteur3D newPosition;
	Vecteur3D newVitesse;
	Vecteur3D newAcceleration;
	this->setPosition(newPosition);
	this->setVitesse(newVitesse);
	this->setAcceleration(newAcceleration);
}

Particule::Particule(Vecteur3D position, Vecteur3D vitesse, Vecteur3D acceleration) {
	this->setPosition(position);
	this->setVitesse(vitesse);
	this->setAcceleration(acceleration);
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

//SETTERS
void Particule::setPosition(Vecteur3D newPosition){
	this->position = newPosition;
}

void Particule::setVitesse(Vecteur3D newVitesse){
	this->vitesse = newVitesse;
}

void Particule::setAcceleration(Vecteur3D newAcceleration){
	this->acceleration = newAcceleration;
}