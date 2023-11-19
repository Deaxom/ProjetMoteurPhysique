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
	double calculNorme() const;
	Vecteur3D calculVecteurUnitaire() const;
	Vecteur3D operator*(double scalaire) const;
	Vecteur3D operator*(const Vecteur3D vec) const;
	Vecteur3D operator+(Vecteur3D vecteur) const;
	Vecteur3D operator-(Vecteur3D vecteur) const;
	double produitScalaire(Vecteur3D vecteur) const;
	Vecteur3D produitVectoriel(Vecteur3D vecteur) const;
	void nettoyerVecteur();
};

