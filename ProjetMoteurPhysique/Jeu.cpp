#include "Jeu.h"
#include "OpenglImGui.h"
#include <iostream>
#include "ParticuleGravite.h"
#include "ParticuleRessortFixe.h"
#include "ParticuleTrainee.h"

//Constructeurs
Jeu::Jeu() {
    this->setEtat(false);
    this->setWindow(nullptr);
    this->setDeltaTime(0.0f);
    this->setLastFrameTime(0.0f);
    Particule* newParticule = new Particule;
    this->setParticule(newParticule);
}

Jeu::Jeu(OpenGlImGui* window, Particule* particule) {
    this->setEtat(false);
    this->setWindow(window);
    this->setDeltaTime(0.0f);
    this->setLastFrameTime(0.0f);
    this->setParticule(particule);
}

Jeu::Jeu(OpenGlImGui* window) {
    this->setEtat(false);
    this->setWindow(window);
    this->setDeltaTime(0.0f);
    this->setLastFrameTime(0.0f);
    Particule* newParticule = new Particule;
    this->setParticule(newParticule);
}

//GETTERS
bool Jeu::getEtat() {
    return this->etat;
}

OpenGlImGui* Jeu::getWindow() {
    return this->window;
}

double Jeu::getDeltaTime() {
    return this->deltaTime;
}

double Jeu::getLastFrameTime() {
    return this->lastFrameTime;
}

Particule* Jeu::getParticule() {
    return this->particule;
}

std::vector<Particule*> Jeu::getListeParticule() {
    return this->listeParticule;
}

//SETTERS
void Jeu::setEtat(bool newEtat) {
    this->etat = newEtat;
}

void Jeu::setWindow(OpenGlImGui* newWindow) {
    this->window = newWindow;
}

void Jeu::setDeltaTime(double newDeltaTime) {
    this->deltaTime = newDeltaTime;
}

void Jeu::setLastFrameTime(double newLastFrameTime) {
    this->lastFrameTime = newLastFrameTime;
}

void Jeu::setParticule(Particule* newParticule) {
    this->particule = newParticule;
}

//Fonction qui démarre le jeu
void Jeu::start() {
    /*glfwMakeContextCurrent(this->getWindow());
    const char* glsl_version = "#version 130";
    OpenGlImGui imgui(window, glsl_version);*/
    this->setEtat(true);
    this->setLastFrameTime(glfwGetTime());

    //particule0 La particule reference au centre du monde
    Vecteur3D positionParticuleReference(0, 0, 0);
    Vecteur3D vitesseParticuleReference(0, 0, 0);
    Vecteur3D accelerationReference(0, 0, 0);

    Particule* particuleReference = new Particule(positionParticuleReference, vitesseParticuleReference, accelerationReference, 10);

    //particule1 Particule soumise à la force de gravite
    Vecteur3D positionParticuleGravite(0, 0, 0);
    Vecteur3D vitesseParticuleGravite(0, 0, 0);
    Vecteur3D accelerationGravite(0, 0, 0);

    Particule* particuleGravite = new Particule(positionParticuleGravite, vitesseParticuleGravite, accelerationGravite, 10);


    //particule2 sur lequel on applique la force de traine
    Vecteur3D positionParticuleTraine(1.5, 0, 0);
    Vecteur3D vitesseParticuleTraine(0.3, 0, 0);
    Vecteur3D accelerationTraine(0, 0, 0);

    Particule* particuleTraine = new Particule(positionParticuleTraine, vitesseParticuleTraine, accelerationTraine, 10);

    //particule3 sur lequel on applique la force de ressort fixe
    Vecteur3D positionParticuleRessortFixe(1, 3, 0);
    Vecteur3D vitesseParticuleRessortFixe(0, 0, 0);
    Vecteur3D accelerationRessortFixe(0.2, 0, 0);

    Particule* particuleRessortFixe = new Particule(positionParticuleRessortFixe, vitesseParticuleRessortFixe, accelerationRessortFixe, 10);


    //On ajoute tout les particules à une liste pour ensuite les afficher graphiquement
    //avec la methode de mise a jour de la class camera (qui est utilise dans le main)
    this->listeParticule = { particuleReference, particuleGravite, particuleTraine, particuleRessortFixe };

    //On cree la force de gravite et on la lie à la particule gravite
    ParticuleGravite *forceGravite = new ParticuleGravite();
    this->forceRegistre.addParticuleForceRegistre(particuleGravite, forceGravite);


    //On cree la force de traine et on la lie à la particule traine
    ParticuleTrainee* forceTrainee = new ParticuleTrainee();
    this->forceRegistre.addParticuleForceRegistre(particuleTraine, forceTrainee);

    //On cree la force de ressort fixe avec une position fixe sur 0,0,0 et on la lie à la particule ressort fixe
    Vecteur3D positionFixe(0, 2, 0);
    float k = 1;
    float restLenght = 2;
    ParticuleRessortFixe* forceRessortFixe = new ParticuleRessortFixe(positionFixe, k, restLenght);
    this->forceRegistre.addParticuleForceRegistre(particuleRessortFixe, forceRessortFixe);
}

//Fonction qui update le jeu à chaque unité de temps
void Jeu::update() {
    if (etat) {
        double currentFrame = glfwGetTime();
        this->setDeltaTime(currentFrame - this->getLastFrameTime());
        this->setLastFrameTime(currentFrame);

        //Le registre applique les forces sur les particules
        forceRegistre.MiseAJourForce(deltaTime);

        std::cout << std::endl;

        for (int i = 0; i < this->listeParticule.size(); i++) {

            std::cout << std::endl;

            integrateur.MiseAJourPositionParticule(listeParticule[i], &deltaTime);
            std::cout << "Particule " << i << " position: (" << listeParticule[i]->getPosition().getX() << "," << listeParticule[i]->getPosition().getY() << "," << listeParticule[i]->getPosition().getZ() << ")" << std::endl;


            integrateur.MiseAJourVelociteParticule(listeParticule[i], &deltaTime);
            std::cout << "Particule " << i << " velocite: (" << listeParticule[i]->getVitesse().getX() << ", " << listeParticule[i]->getVitesse().getY() << ", " << listeParticule[i]->getVitesse().getZ() << ")" << std::endl;

            
            std::cout << "Particule " << i << " acceleration: (" << listeParticule[i]->getAcceleration().getX() << ", " << listeParticule[i]->getAcceleration().getY() << ", " << listeParticule[i]->getAcceleration().getZ() << ")" << std::endl;

            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

//Fonction qui arrête le jeu
void Jeu::stop() {
    //...
    this->setEtat(false);
}