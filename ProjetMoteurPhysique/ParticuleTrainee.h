#pragma once
#include "ParticuleGenerateurForce.h"
class ParticuleTrainee : public ParticuleGenerateurForce
{
private:
	// coeficient de la velocite de trainee
	float m_k1;

	// coeficient au carre
	float m_k2;

	// Coefficients de tra�n�e k1 et k2
	//double k1 = 0.47;  // Exemple pour une sph�re
	//double k2 = 0.001;  // Exemple pour une sph�re
public:
	ParticuleTrainee(float k1, float k2);

	void MiseAJourForce(Particule* particule, double deltaTime);
};

