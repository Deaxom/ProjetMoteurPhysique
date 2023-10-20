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
    Particule newParticule;
    this->setParticule(newParticule);
}

Jeu::Jeu(OpenGlImGui* window, Particule particule) {
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
    Particule newParticule;
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

Particule Jeu::getParticule() {
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

void Jeu::setParticule(Particule newParticule) {
    this->particule = newParticule;
}

//Fonction qui d�marre le jeu
void Jeu::start() {
    /*glfwMakeContextCurrent(this->getWindow());
    const char* glsl_version = "#version 130";
    OpenGlImGui imgui(window, glsl_version);*/
    this->setEtat(true);
    this->setLastFrameTime(glfwGetTime());

    //Particule 1
    Vecteur3D vecteurpositionParticule0(0, 0, 0);
    Vecteur3D vecteurvitesseParticule0(2, 2, 2);
    Vecteur3D vecteuraccelerationParticule0(1, 1, 1);

    Particule* particule0 = new Particule(vecteurpositionParticule0, vecteurvitesseParticule0, vecteuraccelerationParticule0, 10);
    //Particule 2
    Vecteur3D vecteurpositionParticule1(0, 0, 0);
    Vecteur3D vecteurvitesseParticule1(-1, -2, -1);
    Vecteur3D vecteuraccelerationParticule1(-1, -2, 0);

    Particule* particule1 = new Particule(vecteurpositionParticule1, vecteurvitesseParticule1, vecteuraccelerationParticule1, 10);

    //Particule 3
    Vecteur3D vecteurpositionParticule2(0, 0, 0);
    Vecteur3D vecteurvitesseParticule2(1, 2, 3);
    Vecteur3D vecteuraccelerationParticule2(1, 2, 3);

    Particule* particule2 = new Particule(vecteurpositionParticule2, vecteurvitesseParticule2, vecteuraccelerationParticule2, 10);

    this->listeParticule = { particule0, particule1, particule2 };

    ParticuleGravite *forceGravite = new ParticuleGravite();

    this->forceRegistre.addParticuleForceRegistre(particule0 , forceGravite);

}

//Fonction qui update le jeu � chaque unit� de temps
void Jeu::update() {
    if (etat) {
        double currentFrame = glfwGetTime();
        this->setDeltaTime(currentFrame - this->getLastFrameTime());
        this->setLastFrameTime(currentFrame);

        //Test Classe Vecteur3D
        /*std::cout << "Vecteur position: (" << this->getParticule().getPosition().getX() << "," << this->getParticule().getPosition().getY() << "," << this->getParticule().getPosition().getZ() << ")" << std::endl;
        std::cout << "Vecteur vitesse: (" << this->getParticule().getVitesse().getX() << "," << this->getParticule().getVitesse().getY() << "," << this->getParticule().getVitesse().getZ() << ")" << std::endl;
        this->getParticule().setPosition(this->getParticule().getVitesse() + this->getParticule().getVitesse());
        this->getParticule().setVitesse(this->getParticule().getVitesse() + this->getParticule().getAcceleration());*/

        this->getParticule().setPosition(this->getParticule().getPosition() + this->getParticule().getVitesse());

        forceRegistre.MiseAJourForce(deltaTime);

        std::cout << std::endl;

        for (int i = 0; i < 1; i++) { //TODO remettre a 3

            std::cout << std::endl;

            listeParticule[i]->setPosition(integrateur.MiseAJourPositionParticule(listeParticule[i], &deltaTime));
            std::cout << "Particule " << i << " position: (" << listeParticule[i]->getPosition().getX() << "," << listeParticule[i]->getPosition().getY() << "," << listeParticule[i]->getPosition().getZ() << ")" << std::endl;


            listeParticule[i]->setVitesse(integrateur.MiseAJourVelociteParticule(listeParticule[i], &deltaTime));
            std::cout << "Particule " << i << " velocite: (" << listeParticule[i]->getVitesse().getX() << ", " << listeParticule[i]->getVitesse().getY() << ", " << listeParticule[i]->getVitesse().getZ() << ")" << std::endl;

            
            std::cout << "Particule " << i << " acceleration: (" << listeParticule[i]->getAcceleration().getX() << ", " << listeParticule[i]->getAcceleration().getY() << ", " << listeParticule[i]->getAcceleration().getZ() << ")" << std::endl;

            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

//Fonction qui arr�te le jeu
void Jeu::stop() {
    //...
    this->setEtat(false);
}