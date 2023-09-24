#pragma once

struct GLFWwindow;

class OpenGlGLFW
{
public:
	OpenGlGLFW();
	~OpenGlGLFW();

	GLFWwindow* Init();

	bool ShouldClose() const;

	void Update();
	void Renderer();
	void SwapBuffers();


private:
	GLFWwindow* window;
};