#pragma once
#include <glfw3.h>
class Jeu
{
private:
    bool etat;
    GLFWwindow* window;

public:
    Jeu(GLFWwindow* window);
    bool getEtat();
    GLFWwindow* getWindow();
    void setEtat(bool newEtat);
    void setWindow(GLFWwindow* newWindow);
    void start();
    void update();
    void stop();
};

