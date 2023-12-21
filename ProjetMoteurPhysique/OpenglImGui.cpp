// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp

#include "OpenglImGui.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <stdio.h>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <glfw3.h> // Will drag system OpenGL headers

#include "Contact.h"
#include "CorpsRigide.h"

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

float startTime, updateTime = 0.5f;

OpenGlImGui::OpenGlImGui(GLFWwindow* window)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    m_context = ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

OpenGlImGui::~OpenGlImGui()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(m_context);
}

ImGuiContext* OpenGlImGui::GetContext()
{
    return m_context;
}

ImGuiIO* OpenGlImGui::GetIO()
{
    return &ImGui::GetIO();
}

void OpenGlImGui::Render()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void OpenGlImGui::NewFrame()
{

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    {
        ImGui::Begin("Hello, world!");
        ImGui::Text("ZQSD -> move Camera");
        ImGui::Text("P -> pause");
        ImGui::SliderFloat("Display Update Time : ", &updateTime, 0.0f, 5.0f);
        ImGui::End();
    }

    // Affichage des CollisionData
    if (show_another_window)
    {
        ImGui::Begin("Liste de Collisions");
        ImGui::Text("Display Update Time = %f sec", updateTime);
        for (auto contact : contacts)
        {
            ImGui::Text("%s, %s", contact->corpsRigide[0]->name.c_str(), contact->corpsRigide[1]->name.c_str());
            ImGui::Text("ContactPoint = (%f, %f, %f)", contact->contactPoint.getX(), contact->contactPoint.getY(), contact->contactPoint.getZ());
            ImGui::Text("contactNormal = (%f, %f, %f)", contact->contactNormal.getX(), contact->contactNormal.getY(), contact->contactNormal.getZ());
            ImGui::Text("Penetration = %f ", contact->penetration);
            ImGui::Text("restitution = %f ", contact->restitution);
            ImGui::Text("friction = %f ", contact->friction);
            ImGui::NewLine();
        }
        ImGui::End();
    }

    // Rendering
    ImGui::Render();

    float currentTime = glfwGetTime();
    if (currentTime - startTime >= updateTime) {
        show_another_window = false;
    }
}

void OpenGlImGui::DataToShow(Contacts* contacts)
{
    if (!contacts->empty() && !show_another_window)
    {
        this->contacts = *contacts;
        show_another_window = true;
        startTime = glfwGetTime();
    }
}
