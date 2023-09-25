#pragma once
#include <glfw3.h>
#include "Integrateur.h"

class Jeu
{
private:
    bool etat;
    GLFWwindow* window;
    double deltaTime;
    double lastFrameTime;
    Particule particule;

public:
    Jeu();
    Jeu(GLFWwindow* window, Particule particule);
    bool getEtat();
    GLFWwindow* getWindow();
    double getDeltaTime();
    double getLastFrameTime();
    Particule getParticule();
    void setEtat(bool newEtat);
    void setWindow(GLFWwindow* newWindow);
    void setDeltaTime(double newDeltaTime);
    void setLastFrameTime(double newLastFrameTime);
    void setParticule(Particule newParticule);
    void start();
    void update();
    void stop();
};

