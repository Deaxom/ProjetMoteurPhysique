#pragma once
#include "Vecteur3D.h"
#include "Quaternion.h"
#include "Matrix3x4.h"

class CoprsRigide
{
private:
	// Reprise des attributs de particule
	Vecteur3D position;
	Vecteur3D vitesse;
	Vecteur3D acceleration;
	double masse;

	// Par Default = false;
	bool isDynamic;

	Vecteur3D lastVitesse;

	// Orientation du coprs
	Quaternion orientation;

	// Velocite angulaire du coprs
	Vecteur3D velociteAngulaire;

	// Matrice de calcul pour orientation et rotation du coprs
	Matrix3x4 tranformationMatrice;

public:
	// Reprise des methodes de particule
	CoprsRigide();
	CoprsRigide(const Vecteur3D& position, const Vecteur3D& vitesse, const Vecteur3D& acceleration, double masse, bool isDynamic);
	Vecteur3D getPosition() const;
	Vecteur3D getVitesse() const;
	Vecteur3D getAcceleration() const;
	double getMasse();
	bool getIsDynamic();
	Vecteur3D getLastVitesse() const;
	void setPosition(Vecteur3D newPosition);
	void setVitesse(Vecteur3D newVitesse);
	void setAcceleration(Vecteur3D newAcceleration);
	void setMasse(double newMasse);
	void setIsDynamic(bool _isDynamic);
	void setLastVitesse(Vecteur3D _lastVitesse);

	// Methode de modification position, orientation et velocite du coprs
	void MiseAJourCorps(double deltaTime);

private:

	// Methode à appeller chaque frame pour le calcule de la matrice de transformation et la normalisation de l'orientation
	void CalculerTranformationMatrice();
};

