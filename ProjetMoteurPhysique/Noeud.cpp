#include "Noeud.h"

Noeud::Noeud(Noeud* listeEnfant[8], CorpsRigide* listeCorpsRigide) {
	for (int i = 0; i < 8; ++i) {
		this->listeEnfant[i] = listeEnfant[i];
	}
	this->listeCorpsRigide = listeCorpsRigide;
}
