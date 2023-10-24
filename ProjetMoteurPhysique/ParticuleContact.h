#pragma once
#include "Vecteur3D.h"

class Particule;

class ParticuleContact
{
public:
	ParticuleContact();
	~ParticuleContact();

	Particule* particules[2];

	// value 0-1 elasticit� pour la "rebondassibilit�"
	// 1 = collision parfaitement �lastique, 0 perte d'�nergie
	// 0 < e < 1 = collision partiellement elastique, perte partielle d'�nergie
	//0 = coolision non elastique, energie cin�tique perdue
	float restitution;

	// Stocke la profondeur de penetration au contact
	// - float mean no penetration : no action required
	// 0 mean merely touching : no action required
	float penetration;

	Vecteur3D contactNormal;

	void Resolve(float duration);

	float CalculateSeparatingVelocity();

private:
	void ResolveVelocity(float duration);

	// Resolution de l'interpenetration
	void ResolveInterpenetration();

	void CheckResting(int i);

};