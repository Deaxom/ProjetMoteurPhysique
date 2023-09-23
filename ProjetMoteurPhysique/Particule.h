#pragma once
#include "Vecteur3D.h"

class Particule
{
private:
	double positionX;
	double positionY;
	double positionZ;
	Vecteur3D vitesse;
	Vecteur3D acceleration;
public:
	Particule(double positionX, double positionY, double positionZ, Vecteur3D vitesse, Vecteur3D acceleration);
	double getPositionX();
	double getPositionY();
	double getPositionZ();
	Vecteur3D getvitesse();
	Vecteur3D getacceleration();
	void setPositionX(double newPositionX);
	void setPositionY(double newPositionY);
	void setPositionZ(double newPositionZ);
	void setVitesse(Vecteur3D newVitesse);
	void setAcceleration(Vecteur3D newAcceleration);
};

