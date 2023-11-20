#include "OpenglImGui.h"
#include "OpenGlGLFW.h"
#include "Jeu.h"
//#include <glfw3.h> // Will drag system OpenGL headers
#include <iostream>
#include <vector>
#include "CameraControlleur.h"

// Main code
int main(int, char**)
{
    OpenGlGLFW GLFW;
    GLFWwindow* window = GLFW.Init();

    CameraControlleur cameraContolleur;
    cameraContolleur.Init(window);

    // Init by OpenGlImGui class
    OpenGlImGui imgui(window);

    Jeu jeu(&imgui);
    jeu.start();

    bool aKeyPressed = false;
    bool eKeyPressed = false;
    bool rKeyPressed = false;
    bool xKeyPressed = false;
    bool wKeyPressed = false;

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

        //Mise a jour graphique des particules
        //cameraContolleur.MiseAJour(jeu.getListeParticule());

        //Mise a jour graphique des corps rigides
        cameraContolleur.MiseAJour(jeu.getListeCorpsRigide());
        

        imgui.Render();

        GLFW.SwapBuffers();
        
        if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && !aKeyPressed)
        {
            // Interaction utilisateur - Appliquer un torque spécifique
            aKeyPressed = true;
            Vecteur3D torqueUtilisateur(0.0, 1.0, 0.0);
            jeu.getListeCorpsRigide()[8]->AjouterTorque(torqueUtilisateur);
        }
        else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_RELEASE)
        {
            aKeyPressed = false;
        }

        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && !eKeyPressed)
        {
            // Interaction utilisateur - Appliquer un torque spécifique
            eKeyPressed = true;
            Vecteur3D torqueUtilisateur(0.0, 0.0, 1.0);
            jeu.getListeCorpsRigide()[8]->AjouterTorque(torqueUtilisateur);
        }
        else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE)
        {
            eKeyPressed = false;
        }

        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && !rKeyPressed)
        {
            // Interaction utilisateur - Enlever l'accumulateur
            rKeyPressed = true;
            jeu.getListeCorpsRigide()[8]->NettoyerAccumulateur();
        }
        else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE)
        {
            rKeyPressed = false;
        }

        /*if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && !xKeyPressed)
        {
            // Interaction utilisateur - Appliquer une force spécifique
            xKeyPressed = true;
            Vecteur3D forceUtilisateur(1.0, 0.0, 0.0);
            jeu.getListeCorpsRigide()[8]->AjouterForce(forceUtilisateur);
        }
        else if (glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE)
        {
            xKeyPressed = false;
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && !wKeyPressed)
        {
            // Interaction utilisateur - Appliquer une force spécifique
            wKeyPressed = true;
            Vecteur3D forceUtilisateur(-1.0, 0.0, 0.0);
            jeu.getListeCorpsRigide()[8]->AjouterForce(forceUtilisateur);
        }
        else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
        {
            wKeyPressed = false;
        }*/

        jeu.update();
    }

    cameraContolleur.Arret();
    return 0;
}