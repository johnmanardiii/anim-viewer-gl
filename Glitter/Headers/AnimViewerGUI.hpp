#pragma once

#include <string>

struct GLFWwindow;

class AnimViewerGUI
{
public:
	AnimViewerGUI(GLFWwindow* glfwWindow);
	~AnimViewerGUI();

	void DrawAnimViewerGUI();
private:
	void DrawMainMenuBar();
	std::string OpenFileDialogue();

	GLFWwindow* m_glfwWindow;
	bool b_openImportWindow;
};