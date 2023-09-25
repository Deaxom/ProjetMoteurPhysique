#include "Jeu.h"
#include "OpenglImGui.h"
#include <iostream>

//Constructeurs
Jeu::Jeu() {
    this->setEtat(false);
    this->setWindow(nullptr);
    this->setDeltaTime(0.0f);
    this->setLastFrameTime(0.0f);
    Particule newParticule;
    this->setParticule(newParticule);
}

Jeu::Jeu(GLFWwindow* window, Particule particule) {
    this->setEtat(false);
    this->setWindow(window);
    this->setDeltaTime(0.0f);
    this->setLastFrameTime(0.0f);
    this->setParticule(particule);
}

bool Jeu::getEtat() {
    return this->etat;
}

GLFWwindow* Jeu::getWindow() {
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

void Jeu::setEtat(bool newEtat) {
    this->etat = newEtat;
}

void Jeu::setWindow(GLFWwindow* newWindow) {
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

void Jeu::start() {
    /*glfwMakeContextCurrent(this->getWindow());
    const char* glsl_version = "#version 130";
    OpenGlImGui imgui(window, glsl_version);*/
    this->setEtat(true);
    this->setLastFrameTime(glfwGetTime());
}

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

        //Test Classe Integrateur
        Particule Particule(this->getParticule().getPosition(), this->getParticule().getVitesse(), this->getParticule().getAcceleration());
        Integrateur integrateur;
        Particule.setPosition(integrateur.MiseAJourPositionParticule(Particule, deltaTime));
        std::cout << "Particule update position Y : " << Particule.getPosition().getY() << std::endl;

        Particule.setVitesse(integrateur.MiseAJourVelociteParticule(Particule, deltaTime));
        std::cout << "Particule update vitesse X : " << Particule.getVitesse().getX() << std::endl;
    }
}

void Jeu::stop() {
    //...
    this->setEtat(false);
}