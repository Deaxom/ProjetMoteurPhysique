#pragma once
#include "Vecteur3D.h"

class Particule
{
private:
	Vecteur3D position;
	Vecteur3D vitesse;
	Vecteur3D acceleration;
	double masse;
public:
	Particule();
	Particule(const Vecteur3D& position, const Vecteur3D& vitesse, const Vecteur3D& acceleration, double masse);
	Vecteur3D getPosition() const;
	Vecteur3D getVitesse() const;
	Vecteur3D getAcceleration() const;
	double getMasse();
	void setPosition(Vecteur3D newPosition);
	void setVitesse(Vecteur3D newVitesse);
	void setAcceleration(Vecteur3D newAcceleration);
	void setMasse(double newMasse);
};

