#include "OpenGlGLFW.h"

#include <glfw3.h> // Will drag system OpenGL headers
#include <stdio.h>

float clear_color[4] = { 0.45f, 0.55f, 0.60f, 1.00f };

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

OpenGlGLFW::OpenGlGLFW()
{
}

OpenGlGLFW::~OpenGlGLFW()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

GLFWwindow* OpenGlGLFW::Init()
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        window = nullptr;
        return nullptr;
    }

    // Create window with graphics context
    window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 example", nullptr, nullptr);
    if (window == nullptr)
        return window;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    return window;
}

bool OpenGlGLFW::ShouldClose() const
{
    return window == nullptr || glfwWindowShouldClose(window);
}

void OpenGlGLFW::Update()
{
    // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    glfwPollEvents();
}

void OpenGlGLFW::Renderer()
{
    // Rendering
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color[0] * clear_color[3], clear_color[1] * clear_color[3], clear_color[2] * clear_color[3], clear_color[3]);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGlGLFW::SwapBuffers()
{
    glfwSwapBuffers(window);
}