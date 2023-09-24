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

double Jeu::getDeltaTime() {
    return this->deltaTime;
}

double Jeu::getLastFrameTime() {
    return this->lastFrameTime;
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

void Jeu::start() {
    this->setEtat(true);
    glfwMakeContextCurrent(this->getWindow());
    const char* glsl_version = "#version 130";
    OpenGlImGui imgui(window, glsl_version);
    this->setDeltaTime(0.0f);
    this->setLastFrameTime(glfwGetTime());
}

void Jeu::update() {
    if (etat) {
        float currentFrame = static_cast<float>(glfwGetTime());
        this->setDeltaTime(currentFrame - this->getLastFrameTime());
        this->setLastFrameTime(currentFrame);
        //...
    }
}

void Jeu::stop() {
    //...
    this->setEtat(false);
}