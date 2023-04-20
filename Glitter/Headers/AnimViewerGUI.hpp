#pragma once

struct GLFWwindow;

class AnimViewerGUI
{
public:
	AnimViewerGUI(GLFWwindow* glfwWindow);
	~AnimViewerGUI();

	void DrawAnimViewerGUI();
private:
	GLFWwindow* m_glfwWindow;
};