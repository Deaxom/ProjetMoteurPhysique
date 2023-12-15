#pragma once
#include "CorpsRigide.h"
class Noeud
{

public:
	Noeud* listeEnfant[8];
	CorpsRigide* listeCorpsRigide;
	Vecteur3D centre;
	float demiLargeur;

	Noeud() = default;
	Noeud(Noeud* listeEnfant[8], CorpsRigide* listeCorpsRigide);
};
