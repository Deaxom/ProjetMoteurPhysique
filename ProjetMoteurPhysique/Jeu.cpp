#include "Jeu.h"
#include "OpenglImGui.h"

//Constructeur
Jeu::Jeu(GLFWwindow* window) {
    this->setEtat(false);
    this->setWindow(window);
}

bool Jeu::getEtat() {
    return this->etat;
}

GLFWwindow* Jeu::getWindow() {
    return this->window;
}

void Jeu::setEtat(bool newEtat) {
    this->etat = newEtat;
}

void Jeu::setWindow(GLFWwindow* newWindow) {
    this->window = newWindow;
}

void Jeu::start() {
    this->setEtat(true);
    glfwMakeContextCurrent(this->getWindow());
    const char* glsl_version = "#version 130";
    OpenGlImGui imgui(window, glsl_version);
}

void Jeu::update() {
    if (etat) {
        //...
    }
}

void Jeu::stop() {
    //...
    this->setEtat(false);
}