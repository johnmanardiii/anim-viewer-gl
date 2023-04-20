#include "AnimViewerGUI.hpp"
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

AnimViewerGUI::AnimViewerGUI(GLFWwindow* glfwWindow)
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
	ImGui::ShowDemoWindow();

	// render dear imgui onto screen
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
