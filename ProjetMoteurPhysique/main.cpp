#include "Integrateur.h"
#include "OpenglImGui.h"
#include "OpenGlGLFW.h"
#include <glfw3.h> // Will drag system OpenGL headers
#include <iostream>

// Main code
int main(int, char**)
{
    OpenGlGLFW GLFW;
    GLFWwindow* window = GLFW.Init();

    // Init by OpenGlImGui class
    OpenGlImGui imgui(window);

    //Test Classe Vecteur3D
    Vecteur3D vecteurposition(0, 0, 0);
    Vecteur3D vecteurvitesse(0, 2, -1);
    Vecteur3D vecteuracceleration(1, 0, 0);

    //Test Classe Integrateur
    double deltaTime = 0.0f;
    double lastFrameTime = glfwGetTime();

    while (!GLFW.ShouldClose())
    {
        // Graphics Update
        GLFW.Update();

        // Input to stop the app
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        // NewFrame by OpenGlImGui class
        imgui.NewFrame();

        GLFW.Renderer();

        // Draw triangle
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();

        imgui.Render();

        GLFW.SwapBuffers();

        //Test Classe Vecteur3D
        std::cout << "Vecteur position: (" << vecteurposition.getX() << "," << vecteurposition.getY() << "," << vecteurposition.getZ() << ")" << std::endl;
        std::cout << "Vecteur vitesse: (" << vecteurvitesse.getX() << "," << vecteurvitesse.getY() << "," << vecteurvitesse.getZ() << ")" << std::endl;
        vecteurposition = vecteurposition+vecteurvitesse;
        vecteurvitesse = vecteurvitesse+vecteuracceleration;

        //Test Classe Integrateur
         double currentFrameTime = glfwGetTime();
         deltaTime = currentFrameTime - lastFrameTime;
         lastFrameTime = currentFrameTime;

         Particule Particule(vecteurposition, vecteurvitesse, vecteuracceleration);
         Integrateur integrateur;
         Particule.setPosition(integrateur.MiseAJourPositionParticule(Particule, deltaTime));
         std::cout << "Particule update position Y : " << Particule.getPosition().getY() << std::endl;

         Particule.setVitesse(integrateur.MiseAJourVelociteParticule(Particule, deltaTime));
         std::cout << "Particule update vitesse X : " << Particule.getVitesse().getX() << std::endl;
    }

    return 0;
}
