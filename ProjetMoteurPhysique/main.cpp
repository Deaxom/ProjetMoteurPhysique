#include "OpenglImGui.h"
#include "OpenGlGLFW.h"
#include "Jeu.h"
//#include <glfw3.h> // Will drag system OpenGL headers
#include <iostream>
#include <vector>
#include "CameraControlleur.h"
#include "Contact.h"

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

    bool tKeyPressed = false;
    bool eKeyPressed = false;
    bool rKeyPressed = false;

    bool isPlaying = true;
    typedef std::vector<Contact*> Contacts;
    Contacts* contacts;
    contacts = new std::vector<Contact*>;

    while (!GLFW.ShouldClose())
    {

        // Graphics Update
        GLFW.Update();

        // Donnees pour l'affichage des CollisionData
        imgui.DataToShow(contacts);
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
        cameraContolleur.MiseAJour(jeu.getListeCorpsRigide(), isPlaying);
        
        imgui.Render();

        GLFW.SwapBuffers();

        // Test Torque
        if (jeu.getListeCorpsRigide().size() < 3)
        {
            if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && !tKeyPressed)
            {
                // Interaction utilisateur - Appliquer un torque sp�cifique
                tKeyPressed = true;
                Vecteur3D torqueUtilisateur(0.0, 1.0, 0.0);
                jeu.getListeCorpsRigide()[2]->AjouterTorque(torqueUtilisateur);
            }
            else if (glfwGetKey(window, GLFW_KEY_T) == GLFW_RELEASE)
            {
                tKeyPressed = false;
            }

            if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && !eKeyPressed)
            {
                // Interaction utilisateur - Appliquer un torque sp�cifique
                eKeyPressed = true;
                Vecteur3D torqueUtilisateur(0.0, 0.0, 1.0);
                if (jeu.getListeCorpsRigide().size() != 3)
                    continue;
            
                jeu.getListeCorpsRigide()[2]->AjouterTorque(torqueUtilisateur);
            }
            else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE)
            {
                eKeyPressed = false;
            }

            if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && !rKeyPressed)
            {
                // Interaction utilisateur - Enlever l'accumulateur
                rKeyPressed = true;
                //jeu.getListeCorpsRigide()[8]->NettoyerAccumulateur();
                Vecteur3D torqueUtilisateur(0.0, 0.0, -1.0);
                jeu.getListeCorpsRigide()[2]->AjouterTorque(torqueUtilisateur);
            }
            else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE)
            {
                rKeyPressed = false;
            }
        }

        // Pour mettre la physique en pause
        jeu.setEtat(isPlaying);

        // Mise à jours de la Physique
        jeu.update();
        
        // Copier des CollisionData pour l'affichage
        contacts = jeu.GetCollisionList();
    }

    cameraContolleur.Arret();
    return 0;
}