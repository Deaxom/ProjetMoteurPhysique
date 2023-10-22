#pragma once
#include <glfw3.h>
#include "Integrateur.h"
#include "OpenglImGui.h"
#include <vector>
#include "ParticuleForceRegistre.h"

class Jeu
{
private:
    bool etat;
    OpenGlImGui* window;
    double deltaTime;
    double lastFrameTime;
    Integrateur integrateur;
    Particule* particule;
    std::vector<Particule*> listeParticule;
    ParticuleForceRegistre forceRegistre;

public:
    Jeu();
    Jeu(OpenGlImGui* window, Particule* particule);
    Jeu(OpenGlImGui* window);
    bool getEtat();
    OpenGlImGui* getWindow();
    double getDeltaTime();
    double getLastFrameTime();
    Particule* getParticule();
    std::vector<Particule*> getListeParticule();
    void setEtat(bool newEtat);
    void setWindow(OpenGlImGui* newWindow);
    void setDeltaTime(double newDeltaTime);
    void setLastFrameTime(double newLastFrameTime);
    void setParticule(Particule* newParticule);
    void start();
    void update();
    void stop();
};

