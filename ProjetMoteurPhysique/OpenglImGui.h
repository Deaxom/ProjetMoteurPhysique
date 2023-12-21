#pragma once
#include <vector>
struct GLFWwindow;
struct ImGuiContext;
struct ImGuiIO;
//struct ImVec4;
class Contact;


class OpenGlImGui
{
private:
	typedef std::vector<Contact*> Contacts;
	Contacts contacts;
	
public:
	OpenGlImGui(GLFWwindow* window);
	OpenGlImGui(const OpenGlImGui&) = delete;
	OpenGlImGui(OpenGlImGui&&) = delete;
	~OpenGlImGui();

	ImGuiContext* GetContext();
	ImGuiIO* GetIO();

	void Render();

	void NewFrame();

	void DataToShow(Contacts* contacts);

	OpenGlImGui& operator=(const OpenGlImGui&) = delete;
	OpenGlImGui& operator=(OpenGlImGui&&) = delete;


private:
	ImGuiContext* m_context;

	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;

	//ImVec4 clear_color;
};