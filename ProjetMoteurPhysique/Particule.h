#pragma once
#include "Vecteur3D.h"

class Particule
{
private:
	Vecteur3D position;
	Vecteur3D vitesse;
	Vecteur3D acceleration;
	double masse;
	
	// Accumulation de force à appliquer à l'iteration
	// Toujours reset a 0
	Vecteur3D forceAccum;
public:
	Particule();
	Particule(const Vecteur3D& position, const Vecteur3D& vitesse, const Vecteur3D& acceleration, double masse);
	Vecteur3D getPosition() const;
	Vecteur3D getVitesse() const;
	Vecteur3D getAcceleration() const;
	double getMasse();
	Vecteur3D getForceAccum() const;
	void setPosition(Vecteur3D newPosition);
	void setVitesse(Vecteur3D newVitesse);
	void setAcceleration(Vecteur3D newAcceleration);
	void setMasse(double newMasse);
	void clearAccumulator();
	void addForce(const Vecteur3D& force);
};

