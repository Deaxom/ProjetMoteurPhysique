#include "CorpsRigideTrainee.h"
#include <math.h>
#include <cstdlib>

CorpsRigideTrainee::CorpsRigideTrainee(float k1, float k2) :
    m_k1(k1),
    m_k2(k2)
{
}

void CorpsRigideTrainee::MiseAJourForce(CorpsRigide* corpsRigide, double deltaTime) {

    // Coefficients de traînée k1 et k2
    //double k1 = 0.47;  // Exemple pour une sphère
    //double k2 = 0.001;  // Exemple pour une sphère

    Vecteur3D vitesse = corpsRigide->getVitesse();

    // On calcule la norme du vecteur
    double norme = vitesse.calculNorme();

    //On normalise le vecteur
    Vecteur3D vitesseNormalisee = vitesse.calculVecteurUnitaire();

    // On applique la formule de la trainee
    Vecteur3D fdrag = vitesseNormalisee * -1 * (norme * m_k1 + (norme * norme) * m_k2);

    // On calcule l'accélération à partir de la 2eme loi de Newton F=m*a donc a=F/m
    Vecteur3D acceleration = corpsRigide->getAcceleration() + fdrag * (1 / corpsRigide->getMasse());

    // On l'applique à la vitesse du corps rigide
    /*Vecteur3D newVitesse(vitesse + acceleration * deltaTime);
    CorpsRigide->setVitesse(newVitesse);*/
    corpsRigide->setAcceleration(acceleration);
}