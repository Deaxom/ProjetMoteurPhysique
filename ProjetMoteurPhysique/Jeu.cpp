#include "Jeu.h"

//Constructeur
Jeu::Jeu() {
    this->setEtat(false);
}

bool Jeu::getEtat() {
    return this->etat;
}

void Jeu::setEtat(bool newEtat) {
    this->etat = newEtat;
}

void Jeu::start() {
    this->setEtat(true);
}

void Jeu::update() {
    if (etat) {
        //...
    }
}