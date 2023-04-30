#pragma once

#include <string>

class FbxLoader;

struct GLFWwindow;

class AnimViewerGUI
{
public:
	AnimViewerGUI(GLFWwindow* glfwWindow);
	~AnimViewerGUI();

	void DrawAnimViewerGUI();
	void SetFbxLoader(FbxLoader* fbxLoader) { m_fbxLoader = fbxLoader; }
private:
	void DrawMainMenuBar();
	std::string OpenFileDialogue();

	GLFWwindow* m_glfwWindow;
	bool b_openImportWindow;
	FbxLoader* m_fbxLoader;
};