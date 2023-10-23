#pragma once
#include <glfw3.h>
#include "Integrateur.h"
#include "OpenglImGui.h"
#include <vector>
#include "ParticuleForceRegistre.h"
#include "ParticuleContactResolver.h"
#include "ParticuleContactGenerator.h"
#include "Integrateur.h"
#include "ParticuleContact.h"

class Particule;
class ParticuleContact;
class ParticuleContactGenerator;
class ParticuleForceRegistre;
class Integrateur;

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

    ParticuleContactResolver resolver;

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

    typedef std::vector<ParticuleContactGenerator*> ContactGenerator;
    ParticuleForceRegistre forceRegistre;
    ContactGenerator contactGenerators;
    ParticuleContact* contacts;
    int maxContacts;
    int generateContacts();
    void setResolver(unsigned iterations);

    void Intergrate(float duration);
};

