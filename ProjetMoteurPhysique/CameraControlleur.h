#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "../Particule.h"

class Shader;
struct GLFWwindow;
class CorpsRigide;

class CameraControlleur
{
private:
    GLFWwindow* window = nullptr;
    unsigned int texture1, texture2;
    unsigned int VBO, VAO;
    Shader* ourShader = nullptr;

public:
    void Init(GLFWwindow* _window);

    void MiseAJour(std::vector<Particule*> listeParticule, bool &gameState);
    void MiseAJour(std::vector<CorpsRigide*> listeCorpsRigide, bool &gameState);

    void Arret();

};

