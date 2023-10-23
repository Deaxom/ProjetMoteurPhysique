#include "ParticuleTrainee.h"
#include <math.h>
#include <cstdlib>

ParticuleTrainee::ParticuleTrainee(float k1, float k2) :
    m_k1(k1),
    m_k2(k2)
{
}

void ParticuleTrainee::MiseAJourForce(Particule* particule, double deltaTime) {

    Vecteur3D vitesse = particule->getVitesse();

    // On calcule la norme du vecteur
    double norme = vitesse.calculNorme();

    //On normalise le vecteur
    Vecteur3D vitesseNormalisee = vitesse.calculVecteurUnitaire();

    // On applique la formule de la trainee
    Vecteur3D fdrag = vitesseNormalisee * -1 * (norme * m_k1 + (norme * norme) * m_k2);

    // On calcule l'accélération à partir de la 2eme loi de Newton F=m*a donc a=F/m
    //Vecteur3D acceleration = fdrag * (1 / particule->getMasse());

    // On l'applique à la vitesse de la particule
    /*Vecteur3D newVitesse(vitesse + acceleration * deltaTime);
    particule->setVitesse(newVitesse);*/

    particule->addForce(fdrag);
}
