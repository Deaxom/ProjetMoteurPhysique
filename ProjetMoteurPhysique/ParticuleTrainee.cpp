#include "ParticuleTrainee.h"
#include <math.h>
#include <cstdlib>

void ParticuleTrainee::MiseAJourForce(Particule* particule, double deltaTime) {

    // Coefficients de traînée k1 et k2
    double k1 = 0.47;  // Exemple pour une sphère
    double k2 = 0.001;  // Exemple pour une sphère

    Vecteur3D* vitesse = particule->getVitesse();

    // On calcule la norme du vecteur
    double norme = vitesse->calculNorme();

    //On normalise le vecteur
    Vecteur3D vitesseNormalisee = vitesse->calculVecteurUnitaire();

    // On applique la formule de la trainee
    Vecteur3D fdrag = vitesseNormalisee * -1 * (norme * k1 + (norme * norme) * k2);


    // On l'applique à la vitesse de la particule
    Vecteur3D resParticule = particule->getVitesse()->produitVectoriel(fdrag) * (1 / particule->getMasse()) * deltaTime;
    particule->setVitesse(&resParticule);
}
