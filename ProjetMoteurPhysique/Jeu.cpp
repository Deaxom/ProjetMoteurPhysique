#include "Jeu.h"
#include "OpenglImGui.h"
#include <iostream>
#include "ParticuleGravite.h"

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

    //Particule 1
    Vecteur3D* vecteurpositionParticule0 = new Vecteur3D(0, 0, 0);
    Vecteur3D* vecteurvitesseParticule0 = new Vecteur3D(2, 2, 2);
    Vecteur3D* vecteuraccelerationParticule0 = new Vecteur3D(1, 1, 1);

    Particule* particule0 = new Particule(vecteurpositionParticule0, vecteurvitesseParticule0, vecteuraccelerationParticule0, 10);
    //Particule 2
    Vecteur3D* vecteurpositionParticule1 = new Vecteur3D(0, 0, 0);
    Vecteur3D* vecteurvitesseParticule1 = new Vecteur3D(-1, -2, -1);
    Vecteur3D* vecteuraccelerationParticule1 = new Vecteur3D(-1, -2, 0);

    Particule* particule1 = new Particule(vecteurpositionParticule1, vecteurvitesseParticule1, vecteuraccelerationParticule1, 10);

    //Particule 3
    Vecteur3D* vecteurpositionParticule2 = new Vecteur3D(0, 0, 0);
    Vecteur3D* vecteurvitesseParticule2 = new Vecteur3D(1, 2, 3);
    Vecteur3D* vecteuraccelerationParticule2 = new Vecteur3D(1, 2, 3);

    Particule* particule2 = new Particule(vecteurpositionParticule2, vecteurvitesseParticule2, vecteuraccelerationParticule2, 10);

    this->listeParticule = { particule0, particule1, particule2 };

    ParticuleGravite *forceGravite = new ParticuleGravite();

    this->forceRegistre.addParticuleForceRegistre(particule0 , forceGravite);

}

//Fonction qui update le jeu à chaque unité de temps
void Jeu::update() {
    if (etat) {
        double currentFrame = glfwGetTime();
        this->setDeltaTime(currentFrame - this->getLastFrameTime());
        this->setLastFrameTime(currentFrame);

        forceRegistre.MiseAJourForce(deltaTime);

        std::cout << std::endl;

        for (int i = 0; i < 1; i++) { //TODO remettre a 3

            std::cout << std::endl;

            listeParticule[i]->setPosition(&integrateur.MiseAJourPositionParticule(listeParticule[i], &deltaTime));
            std::cout << "Particule " << i << " position: (" << listeParticule[i]->getPosition()->getX() << "," << listeParticule[i]->getPosition()->getY() << "," << listeParticule[i]->getPosition()->getZ() << ")" << std::endl;


            listeParticule[i]->setVitesse(&integrateur.MiseAJourVelociteParticule(listeParticule[i], &deltaTime));
            std::cout << "Particule " << i << " velocite: (" << listeParticule[i]->getVitesse()->getX() << ", " << listeParticule[i]->getVitesse()->getY() << ", " << listeParticule[i]->getVitesse()->getZ() << ")" << std::endl;

            
            std::cout << "Particule " << i << " acceleration: (" << listeParticule[i]->getAcceleration()->getX() << ", " << listeParticule[i]->getAcceleration()->getY() << ", " << listeParticule[i]->getAcceleration()->getZ() << ")" << std::endl;

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