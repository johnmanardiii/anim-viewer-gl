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
	void GetHeightAndWidth(int* width, int* height);
	float GetAspectRatio();
	double GetDeltaTime();
private:
	double previousTime;
	GLFWwindow* glfwWindow;
	bool isValid;
};