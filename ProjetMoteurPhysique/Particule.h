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
	double getPositionX();
	double getPositionY();
	double getPositionZ();
	Vecteur3D getvitesse();
	Vecteur3D getacceleration();
	void setPositionX();
	void setPositionY();
	void setPositionZ();
	void setvitesse();
	void setacceleration();
};

