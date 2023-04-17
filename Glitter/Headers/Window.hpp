#pragma once

struct GLFWwindow;

class Window
{
public:
	// calls 
	Window(int mWidth, int mHeight);
	~Window();
	GLFWwindow* GetGLFWWindow();
	bool ShouldClose();
	bool IsValid();
	void Terminate();
	// swaps gl buffers and polls events
	void SwapBuffersAndPollEvents();
private:
	GLFWwindow* glfwWindow;
	bool isValid;
};