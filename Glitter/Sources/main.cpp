// Local Headers
#include "glitter.hpp"
#include "Window.hpp"

// Standard Headers
#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <fbxsdk.h>
#include <nfd.h>
#include <stdlib.h>

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

int main(int argc, char * argv[]) {
    Window window = Window(mWidth, mHeight);
    if (!window.IsValid())
    {
        return EXIT_FAILURE;
    }
    
    // imgui test code:
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window.GetGLFWWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 150");

    // Rendering Loop
    while (!window.ShouldClose()) {
        
        // TODO: move this into a "renderer" class
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


		// Start a new ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
        ImGui::ShowDemoWindow();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.SwapBuffersAndPollEvents();
    }

	// Clean up
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

    window.Terminate();
    return EXIT_SUCCESS;
}
