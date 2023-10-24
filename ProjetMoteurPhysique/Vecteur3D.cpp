#include "Vecteur3D.h"
#include <math.h>

//Constructeurs
Vecteur3D::Vecteur3D() {
	this->setX(0);
	this->setY(0);
	this->setZ(0);
}

Vecteur3D::Vecteur3D(double x, double y, double z) {
	this->setX(x);
	this->setY(y);
	this->setZ(z);
}

//GETTERS
double Vecteur3D::getX() {
	return this->x;
}

double Vecteur3D::getY() {
	return this->y;
}

double Vecteur3D::getZ() {
	return this->z;
}

//SETTERS
void Vecteur3D::setX(double newX) {
	this->x = newX;
}

void Vecteur3D::setY(double newY) {
	this->y = newY;
}

void Vecteur3D::setZ(double newZ) {
	this->z = newZ;
}

//Calcul de la norme du vecteur, renvoie un double
double Vecteur3D::calculNorme() {
	double x2 = this->x * this->x;
	double y2 = this->y * this->y;
	double z2 = this->z * this->z;
	return sqrt(x2 + y2 + z2);
}

//Calcul du vecteur unitaire, renvoie un autre Vecteur3D
Vecteur3D Vecteur3D::calculVecteurUnitaire() {
	double norme = this->calculNorme();
	if (norme == 0.0) return Vecteur3D(0.0, 0.0, 0.0);
	double newX = this->x / norme;
	double newY = this->y / norme;
	double newZ = this->z / norme;
	return Vecteur3D(newX, newY, newZ);
}

//Calcul de la multiplication par un scalaire, renvoie un autre Vecteur3D
Vecteur3D Vecteur3D::operator*(double scalaire) {
	double newX = this->x * scalaire;
	double newY = this->y * scalaire;
	double newZ = this->z * scalaire;
	return Vecteur3D(newX, newY, newZ);
}

Vecteur3D Vecteur3D::operator*(const Vecteur3D vec)
{
	return Vecteur3D(x * vec.x, y * vec.y, z * vec.z);
}

//Calcul de l'addition entre 2 Vecteur3D, renvoie un autre Vecteur3D
Vecteur3D Vecteur3D::operator+(Vecteur3D vecteur) {
	double newX = this->x + vecteur.getX();
	double newY = this->y + vecteur.getY();
	double newZ = this->z + vecteur.getZ();
	return Vecteur3D(newX, newY, newZ);
}

//Calcul de la soustraction entre 2 Vecteur3D, renvoie un autre Vecteur3D
Vecteur3D Vecteur3D::operator-(Vecteur3D vecteur) {
	double newX = this->x - vecteur.getX();
	double newY = this->y - vecteur.getY();
	double newZ = this->z - vecteur.getZ();
	return Vecteur3D(newX, newY, newZ);
}

//Calcul du produit scalaire entre 2 Vecteur3D, renvoie un double
double Vecteur3D::produitScalaire(Vecteur3D vecteur) {
	double sumX = this->x * vecteur.getX();
	double sumY = this->y * vecteur.getY();
	double sumZ = this->z * vecteur.getZ();
	return (sumX + sumY + sumZ);
}

//Calcul du produit vectoriel entre 2 Vecteur3D, renvoie un autre Vecteur3D
Vecteur3D Vecteur3D::produitVectoriel(Vecteur3D vecteur) {
	double newX = this->y * vecteur.getZ() - this->z * vecteur.getY();
	double newY = this->z * vecteur.getX() - this->x * vecteur.getZ();
	double newZ = this->x * vecteur.getY() - this->y * vecteur.getX();
	return Vecteur3D(newX, newY, newZ);
}