#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "../Particule.h"

class Shader;
struct GLFWwindow;

class CameraControlleur
{
private:
    GLFWwindow* window = nullptr;
    unsigned int texture1, texture2;
    unsigned int VBO, VAO;
    Shader* ourShader = nullptr;

    // Test Particule qui bouge
    Particule* pa;
    glm::vec3 po;
    //Fin Test Particule qui bouge

    // world space positions of our cubes
    glm::vec3 cubePositions[10] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

public:
    void Init(GLFWwindow* _window);

    void MiseAJour();

    void Arret();
};

