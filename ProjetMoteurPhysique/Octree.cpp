#include "Octree.h"

Noeud* Octree::construireOctree(Vecteur3D centre, float demiLargeur, int profondeurOctree)
{
	if (profondeurOctree < 0) {
		return NULL;
	}
	else
	{
		Noeud* pNoeud = new Noeud;
		pNoeud->centre = centre;
		pNoeud->demiLargeur = demiLargeur;
		pNoeud->listeCorpsRigide = NULL;

		Vecteur3D decalage;
		float nouvelleDemiLargeur = demiLargeur * 0.5f;
		for (size_t i = 0; i < 8; i++)
		{
			decalage.setX(((i & 1) ? nouvelleDemiLargeur : -nouvelleDemiLargeur));
			decalage.setY(((i & 2) ? nouvelleDemiLargeur : -nouvelleDemiLargeur));
			decalage.setZ(((i & 4) ? nouvelleDemiLargeur : -nouvelleDemiLargeur));
			pNoeud->listeEnfant[i] = construireOctree(centre + decalage, nouvelleDemiLargeur, profondeurOctree - 1);
		}
		return pNoeud;
	}
}

void Octree::InsererCorpsRigideOctree(Noeud* arbre, CorpsRigide* corpsRigide)
{
	int indexEnfant = 0;
	bool chevauchement = false;

	double deltaX = corpsRigide->getPosition().getX() - arbre->centre.getX();
	double deltaY = corpsRigide->getPosition().getY() - arbre->centre.getY();
	double deltaZ = corpsRigide->getPosition().getZ() - arbre->centre.getZ();

	// On verifie que le corps rigide ne chevauche pas un plan de la division de octree
	if (std::abs(deltaX) <= corpsRigide->getRayonCorps() ||
		std::abs(deltaY) <= corpsRigide->getRayonCorps() ||
		std::abs(deltaZ) <= corpsRigide->getRayonCorps()) {
		chevauchement = true;
	}

	// On modifie index en fonction position de notre corps rigide
	if (deltaX > 0.0) {
		indexEnfant |= 1;
	}
	if (deltaY > 0.0) {
		indexEnfant |= 2;
	}
	if (deltaZ > 0.0) {
		indexEnfant |= 4;
	}

	if (!chevauchement) {
		if (arbre->listeEnfant[indexEnfant] == NULL) {
			arbre->listeEnfant[indexEnfant] = new Noeud;
		}

		InsererCorpsRigideOctree(arbre->listeEnfant[indexEnfant], corpsRigide);
	}
	else {
		corpsRigide->setCorpsRigideSuivant(arbre->listeCorpsRigide);
		arbre->listeCorpsRigide = corpsRigide;
	}
}
