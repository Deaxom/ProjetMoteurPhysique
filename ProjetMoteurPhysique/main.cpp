#include "OpenglImGui.h"
#include "OpenGlGLFW.h"
#include "Jeu.h"
//#include <glfw3.h> // Will drag system OpenGL headers
#include <iostream>
#include <vector>

// Main code
//int main(int, char**)
//{
//    OpenGlGLFW GLFW;
//    GLFWwindow* window = GLFW.Init();
//
//    // Init by OpenGlImGui class
//    OpenGlImGui imgui(window);
//
//    Jeu jeu(&imgui);
//    jeu.start();
//
//    while (!GLFW.ShouldClose())
//    {
//
//        // Graphics Update
//        GLFW.Update();
//
//        // Input to stop the app
//        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//            glfwSetWindowShouldClose(window, true);
//
//        // NewFrame by OpenGlImGui class
//        imgui.NewFrame();
//
//        GLFW.Renderer();
//
//        // Draw triangle
//        glBegin(GL_TRIANGLES);
//        glVertex2f(-0.5f, -0.5f);
//        glVertex2f(0.0f, 0.5f);
//        glVertex2f(0.5f, -0.5f);
//        glEnd();
//
//        imgui.Render();
//
//        GLFW.SwapBuffers();
//        
//        jeu.update();
//    }
//
//    return 0;
//}