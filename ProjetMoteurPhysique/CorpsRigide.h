#pragma once
#include "Vecteur3D.h"

#include "Matrix3x4.h"
#include "Matrix3x3.h"

class Primitive;
struct PrimitiveSet;

class CorpsRigide
{
private:
	// Reprise des attributs de particule
	Vecteur3D position;
	Vecteur3D vitesse;
	Vecteur3D acceleration;
	double masse;

	Vecteur3D lastVitesse;

	// Orientation du corps
	Quaternion orientation;

	// Velocite angulaire du corps
	Vecteur3D velociteAngulaire;

	Vecteur3D accelerationAngulaire;

	// Matrice de calcul pour orientation et rotation du corps
	Matrix3x4 transformationMatrice;

	Matrix3x3 tenseurInertieInverse;

	float traineeAngulaire;

	Vecteur3D forceAccumulateur;

	Vecteur3D torqueAccumulateur;


	//Attribut de volume englobant corps rigide pour octree
	float rayonCoprs;
	CorpsRigide* corpsRigideSuivant;

	//Primitives du CorpsRigide
	/*PrimitiveSet* primitiveSet;
	Primitive* primitive;*/

public:
	// Reprise des methodes de particule
	CorpsRigide();
	CorpsRigide(Vecteur3D& position, const Vecteur3D& vitesse, const Vecteur3D& acceleration, double masse, Quaternion orientation, Vecteur3D velociteAngulaire, Vecteur3D accelerationAngulaire, Matrix3x3 tenseurInertie);
	Vecteur3D getPosition();
	Vecteur3D getVitesse() const;
	Vecteur3D getAcceleration() const;
	double getMasse();
	Vecteur3D getLastVitesse() const;
	Quaternion getOrientation() const;
	Vecteur3D getVelociteAngulaire() const;
	Vecteur3D getAccelerationAngulaire() const;
	Matrix3x4 getTransmationMatrice() const;
	Matrix3x3 getTenseurInertieInverse() const;
	Vecteur3D getForceAccumulateur() const;
	Vecteur3D getTorqueAccumulateur() const;
	float getRayonCorps() const;
	CorpsRigide* getCorpsRigideSuivant() const;
	void setPosition(Vecteur3D newPosition);
	void setVitesse(Vecteur3D newVitesse);
	void setAcceleration(Vecteur3D newAcceleration);
	void setMasse(double newMasse);
	void setLastVitesse(Vecteur3D _lastVitesse);
	void setOrientation(Quaternion& orientation);
	void SetVelociteAngulaire(Vecteur3D& velociteAngulaire);
	void SetAccelerationAngulaire(Vecteur3D& accelerationAngulaire);
	void SetTransformationMatrice(Matrix3x4 transformationMatrice);

	//On met le tenseur initial et il sera inverse dans le setter
	void SetTenseurInertieInverse(Matrix3x3 tenseurInertie);

	void setRayonCorps(float rayon);
	void setCorpsRigideSuivant(CorpsRigide* corpsRigideSuivant);

	
	void AjouterForce(const Vecteur3D& force);
	void AjouterForcePointMonde(const Vecteur3D& force, const Vecteur3D& pointMonde);
	void AjouterForcePointCorps(const Vecteur3D& force, const Vecteur3D& pointCorps);
	
	void AjouterTorque(const Vecteur3D& torque);
	void AjouterTorquePointMonde(const Vecteur3D& force, const Vecteur3D& pointMonde);
	void AjouterTorquePointCorps(const Vecteur3D& force, const Vecteur3D& pointCorps);

	void NettoyerAccumulateur();

	//void MiseAJourCorps(double &deltaTime);

	// Methode appeller chaque frame pour le calcule de la matrice de transformation et la normalisation de l'orientation
	void CalculerTransformationMatrice();

	PrimitiveSet* primitiveSet;
	Primitive* primitive;

};
