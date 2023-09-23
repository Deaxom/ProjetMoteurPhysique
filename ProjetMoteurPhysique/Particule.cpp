#include "Particule.h"

//Constructeur
Particule::Particule(double positionX, double positionY, double positionZ, Vecteur3D vitesse, Vecteur3D acceleration) {
	this->setPositionX(positionX);
	this->setPositionY(positionY);
	this->setPositionZ(positionZ);
	this->setVitesse(vitesse);
	this->setAcceleration(acceleration);
}

//GETTERS
double Particule::getPositionX() {
	return this->positionX;
}

double Particule::getPositionY() {
	return this->positionY;
}

double Particule::getPositionZ(){
	return this->positionZ;
}

Vecteur3D Particule::getvitesse(){
	return this->vitesse;
}

Vecteur3D Particule::getacceleration(){
	return this->acceleration;
}

//SETTERS
void Particule::setPositionX(double newPositionX){
	this->positionX = newPositionX;
}

void Particule::setPositionY(double newPositionY){
	this->positionY = newPositionY;
}

void Particule::setPositionZ(double newPositionZ){
	this->positionZ = newPositionZ;
}

void Particule::setVitesse(Vecteur3D newVitesse){
	this->vitesse = newVitesse;
}

void Particule::setAcceleration(Vecteur3D newAcceleration){
	this->acceleration = newAcceleration;
}