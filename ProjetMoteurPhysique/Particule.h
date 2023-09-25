#pragma once
#include "Vecteur3D.h"

class Particule
{
private:
	Vecteur3D position;
	Vecteur3D vitesse;
	Vecteur3D acceleration;
public:
	Particule();
	Particule(Vecteur3D position, Vecteur3D vitesse, Vecteur3D acceleration);
	Vecteur3D getPosition();
	Vecteur3D getVitesse();
	Vecteur3D getAcceleration();
	void setPosition(Vecteur3D newPosition);
	void setVitesse(Vecteur3D newVitesse);
	void setAcceleration(Vecteur3D newAcceleration);
};

