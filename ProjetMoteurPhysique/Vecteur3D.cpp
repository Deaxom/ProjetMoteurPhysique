#include "Vecteur3D.h"
#include <math.h>

Vecteur3D::Vecteur3D(double x, double y, double z) {
	this->setX(x);
	this->setY(y);
	this->setZ(z);
}

double Vecteur3D::getX() {
	return this->x;
}

double Vecteur3D::getY() {
	return this->y;
}

double Vecteur3D::getZ() {
	return this->z;
}

void Vecteur3D::setX(double newX) {
	this->x = newX;
}

void Vecteur3D::setY(double newY) {
	this->y = newY;
}

void Vecteur3D::setZ(double newZ) {
	this->z = newZ;
}

double Vecteur3D::calculNorme() {
	double x2 = this->x * this->x;
	double y2 = this->y * this->y;
	double z2 = this->z * this->z;
	return sqrt(x2 + y2 + z2);
}

Vecteur3D Vecteur3D::calculVecteurUnitaire() {
	double norme = this->calculNorme();
	double newX = this->x / norme;
	double newY = this->y / norme;
	double newZ = this->z / norme;
	return Vecteur3D(newX, newY, newZ);
}

Vecteur3D Vecteur3D::multiplicationScalaire(double scalaire) {
	double newX = this->x * scalaire;
	double newY = this->y * scalaire;
	double newZ = this->z * scalaire;
	return Vecteur3D(newX, newY, newZ);
}

Vecteur3D Vecteur3D::addition(Vecteur3D vecteur) {
	double newX = this->x + vecteur.getX();
	double newY = this->y + vecteur.getY();
	double newZ = this->z + vecteur.getZ();
	return Vecteur3D(newX, newY, newZ);
}

Vecteur3D Vecteur3D::soustraction(Vecteur3D vecteur) {
	double newX = this->x - vecteur.getX();
	double newY = this->y - vecteur.getY();
	double newZ = this->z - vecteur.getZ();
	return Vecteur3D(newX, newY, newZ);
}

double Vecteur3D::produitScalaire(Vecteur3D vecteur) {

}