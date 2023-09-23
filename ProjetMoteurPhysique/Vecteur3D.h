#pragma once
class Vecteur3D
{
private:
	double x;
	double y;
	double z;
public:
	Vecteur3D();
	Vecteur3D(double x, double y, double z);
	double getX();
	double getY();
	double getZ();
	void setX(double newX);
	void setY(double newY);
	void setZ(double newZ);
	double calculNorme();
	Vecteur3D calculVecteurUnitaire();
	Vecteur3D multiplicationScalaire(double scalaire);
	Vecteur3D addition(Vecteur3D vecteur);
	Vecteur3D soustraction(Vecteur3D vecteur);
	double produitScalaire(Vecteur3D vecteur);
	Vecteur3D produitVectoriel(Vecteur3D vecteur);
};

