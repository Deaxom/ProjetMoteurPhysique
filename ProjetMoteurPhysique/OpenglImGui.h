#pragma once
struct GLFWwindow;
struct ImGuiContext;
struct ImGuiIO;
//struct ImVec4;

class OpenGlImGui
{
public:
	OpenGlImGui(GLFWwindow* window);
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

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;

	//ImVec4 clear_color;
};