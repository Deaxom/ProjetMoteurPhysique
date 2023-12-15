#include "Noeud.h"
#pragma once
class Octree
{

	//Citer le livre erisson car je m en suis inspire
public:
	static Noeud* construireOctree(Vecteur3D centre, float demiLargeur, int profondeurOctree);
	static void InsererCorpsRigideOctree(Noeud* arbre, CorpsRigide* corpsRigide);
};

