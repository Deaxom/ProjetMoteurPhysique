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
		pNoeud->tailleListeCorpsRigide = 0;

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
	//Si vrai le corps est a droite du centre 
	if (deltaX > 0.0) {
		indexEnfant |= 1;
	}
	//Si vrai le corps est au dessus du centre 
	if (deltaY > 0.0) {
		indexEnfant |= 2;
	}
	//Si vrai le corps est devant le centre 
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
		arbre->tailleListeCorpsRigide++;

		//std::cout << "add octree: " << corpsRigide->getPosition().getX() << std::endl;
	}
}

void Octree::DetecterCollisionsPotentielles(Noeud* arbre)
{
	// V�rifier les collisions potentielles pour les objets dans ce n�ud
	VerifierCollisionsPotentiellesNoeud(arbre);

	// v�rifier les collisions potentielles pour les enfants du n�ud
	for (int i = 0; i < 8; ++i)
	{
		if (arbre->listeEnfant[i] != NULL)
		{
			DetecterCollisionsPotentielles(arbre->listeEnfant[i]);
		}
	}
}

void Octree::VerifierCollisionsPotentiellesNoeud(Noeud* noeud)
{
	// V�rifier les collisions potentielles pour ce n�ud
	CorpsRigide* corpsRigide1 = noeud->listeCorpsRigide;
	while (corpsRigide1 != NULL)
	{
		CorpsRigide* corpsRigide2 = noeud->listeCorpsRigide;
		while (corpsRigide2 != NULL)
		{
			if (corpsRigide1 != corpsRigide2)
			{

				// Calculer la distance entre les centres des sph�res englobantes
				Vecteur3D distance = corpsRigide1->getPosition() - corpsRigide2->getPosition();
				double distanceSquared = distance.getX() * distance.getX() + distance.getY() * distance.getY() + distance.getZ() * distance.getZ();


				// Calculer la somme des rayons des sph�res englobantes
				double rayonTotal = corpsRigide1->getRayonCorps() + corpsRigide2->getRayonCorps();
				double rayonTotalSquared = rayonTotal * rayonTotal;

				// V�rifier si la distance est inf�rieure � la somme des rayons
				if (distanceSquared <= rayonTotalSquared) {
			
					std::cout 
						<< "Collision potentielle entre les corps rigides "
						<< corpsRigide1->getPosition().getX() << corpsRigide1->getPosition().getY() << corpsRigide1->getPosition().getZ() 
						<< " et " 
						<< corpsRigide2->getPosition().getX() << corpsRigide2->getPosition().getY() << corpsRigide2->getPosition().getZ() 
						<< std::endl;
				}
				
			}
			corpsRigide2 = corpsRigide2->getCorpsRigideSuivant();
		}
		corpsRigide1 = corpsRigide1->getCorpsRigideSuivant();
	}
}
