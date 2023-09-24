#pragma once
struct GLFWwindow;
struct ImGuiContext;
struct ImGuiIO;

class OpenGlImGui
{
public:
	OpenGlImGui(GLFWwindow* window, const char* glsl_version);
	OpenGlImGui(const OpenGlImGui&) = delete;
	OpenGlImGui(OpenGlImGui&&) = delete;
	~OpenGlImGui();

	ImGuiContext* GetContext();
	ImGuiIO* GetIO();

	void Render();

	void NewFrame();

	OpenGlImGui& operator=(const OpenGlImGui&) = delete;
	OpenGlImGui& operator=(OpenGlImGui&&) = delete;

private:
	ImGuiContext* m_context;
};