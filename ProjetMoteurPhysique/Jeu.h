#pragma once
#include <glfw3.h>
class Jeu
{
private:
    bool etat;
    GLFWwindow* window;
    double deltaTime;
    double lastFrameTime;

public:
    Jeu(GLFWwindow* window);
    bool getEtat();
    GLFWwindow* getWindow();
    double getDeltaTime();
    double getLastFrameTime();
    void setEtat(bool newEtat);
    void setWindow(GLFWwindow* newWindow);
    void setDeltaTime(double newDeltaTime);
    void setLastFrameTime(double newLastFrameTime);
    void start();
    void update();
    void stop();
};

