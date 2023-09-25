#include "OpenglImGui.h"
#include "OpenGlGLFW.h"
#include "Jeu.h"
//#include <glfw3.h> // Will drag system OpenGL headers
#include <iostream>
#include <vector>

// Main code
int main(int, char**)
{
    OpenGlGLFW GLFW;
    GLFWwindow* window = GLFW.Init();

    // Init by OpenGlImGui class
    OpenGlImGui imgui(window);
    Jeu jeu(&imgui, Particule(Vecteur3D(0, 0, 0), Vecteur3D(2, 2, 2), Vecteur3D(1, 1, 1)));

    //Test Classe Integrateur
    double deltaTime = 0.0f;
    double lastFrameTime = glfwGetTime();
    Integrateur integrateur;


    //Particule 1
    Vecteur3D vecteurpositionParticule0(0, 0, 0);
    Vecteur3D vecteurvitesseParticule0(2, 2, 2);
    Vecteur3D vecteuraccelerationParticule0(1, 1, 1);

    Particule particule0(vecteurpositionParticule0, vecteurvitesseParticule0, vecteuraccelerationParticule0);

    //Particule 2
    Vecteur3D vecteurpositionParticule1(0, 0, 0);
    Vecteur3D vecteurvitesseParticule1(-1, -2, -1);
    Vecteur3D vecteuraccelerationParticule1(-1, -2, 0);

    Particule particule1(vecteurpositionParticule1, vecteurvitesseParticule1, vecteuraccelerationParticule1);

    //Particule 3
    Vecteur3D vecteurpositionParticule2(0, 0, 0);
    Vecteur3D vecteurvitesseParticule2(1, 2, 3);
    Vecteur3D vecteuraccelerationParticule2(1, 2, 3);

    Particule particule2(vecteurpositionParticule2, vecteurvitesseParticule2, vecteuraccelerationParticule2);


    std::vector<Particule> listeParticule = { particule0, particule1 , particule2 };

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

        //Test Classe Integrateur
        double currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        for (int i = 0; i < listeParticule.size(); i++) {

            std::cout << std::endl;

            listeParticule[i].setPosition(integrateur.MiseAJourPositionParticule(listeParticule[i], deltaTime));
            std::cout << "Particule " << i << " position: (" << listeParticule[i].getPosition().getX() << "," << listeParticule[i].getPosition().getY() << "," << listeParticule[i].getPosition().getZ() << ")" << std::endl;


            listeParticule[i].setVitesse(integrateur.MiseAJourVelociteParticule(listeParticule[i], deltaTime));
            std::cout << "Particule " << i << " velocite: (" << listeParticule[i].getVitesse().getX() << ", " << listeParticule[i].getVitesse().getY() << ", " << listeParticule[i].getVitesse().getZ() << ")" << std::endl;

            std::cout << std::endl;
        }

    }

    return 0;
}
