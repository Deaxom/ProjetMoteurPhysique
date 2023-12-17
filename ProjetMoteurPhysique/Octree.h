#pragma once
#include "Noeud.h"
#include <vector>
class Octree
{

	//Citer le livre erisson car je m en suis inspire
public:
	 Noeud* construireOctree(Vecteur3D centre, float demiLargeur, int profondeurOctree);
	 void InsererCorpsRigideOctree(Noeud* arbre, CorpsRigide* corpsRigide);
	 void DetecterCollisionsPotentielles(Noeud* arbre, std::vector<std::pair<CorpsRigide*, CorpsRigide*>> *listPairCollider);
	 void VerifierCollisionsPotentiellesNoeud(Noeud* noeud, std::vector<std::pair<CorpsRigide*, CorpsRigide*>> *listPairCollider);
};

