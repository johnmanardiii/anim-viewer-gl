#include "AnimViewerGUI.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "nfd.h"

/*
	There should really only be one instance of this class, and that should be enforced in code, but this is a prototype.
*/
AnimViewerGUI::AnimViewerGUI(GLFWwindow* glfwWindow) : b_openImportWindow(false)
{
	m_glfwWindow = glfwWindow;

	// imgui test code:
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(m_glfwWindow, true);
	ImGui_ImplOpenGL3_Init("#version 150");
	ImGui::StyleColorsDark();
}

AnimViewerGUI::~AnimViewerGUI()
{
	// Clean up
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void AnimViewerGUI::DrawAnimViewerGUI()
{
	// Feed input into imgui and start new frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// actual rendering of the GUI
	DrawMainMenuBar();
	// ImGui::ShowDemoWindow();	// This is for understanding ImGui

	// render dear imgui onto screen
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void AnimViewerGUI::DrawMainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::MenuItem("Open FBX File", NULL, &b_openImportWindow, true);
			// ShowExampleMenuFile();
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	// respond to input for this frame:
	if (b_openImportWindow)
	{
		// disable the variable that controls the file explorer
		b_openImportWindow = false;
		// open the dialog to open the fbx file:
		std::string FBXPath = OpenFileDialogue();
		std::cout << "Opening Fbx: " <<  FBXPath << std::endl;
	}
}

std::string AnimViewerGUI::OpenFileDialogue()
{
	std::string filePath;

	nfdchar_t* outPath = NULL;
	nfdresult_t result = NFD_OpenDialog("fbx", NULL, &outPath);

	if (result == NFD_OKAY) {
		filePath = std::string(outPath);
		free(outPath);
	}
	else if(result != NFD_CANCEL) {
		std::cout << "Error Opening File: " << NFD_GetError() << std::endl;
	}

	return filePath;
}
