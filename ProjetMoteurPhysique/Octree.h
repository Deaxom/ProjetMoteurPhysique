#include "Noeud.h"
#pragma once
class Octree
{

	//Citer le livre erisson car je m en suis inspire
public:
	 Noeud* construireOctree(Vecteur3D centre, float demiLargeur, int profondeurOctree);
	 void InsererCorpsRigideOctree(Noeud* arbre, CorpsRigide* corpsRigide);
	 void DetecterCollisionsPotentielles(Noeud* arbre);
	 void VerifierCollisionsPotentiellesNoeud(Noeud* noeud);
};

