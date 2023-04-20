// Local Headers
#include "glitter.hpp"
#include "Window.hpp"
#include "AnimViewerGUI.hpp"

// Standard Headers
#include <cstdio>
#include <cstdlib>

#include <iostream>
#include <fbxsdk.h>
#include <nfd.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    Window window = Window(mWidth, mHeight);
    if (!window.IsValid())
    {
        return EXIT_FAILURE;
    }

    // initialize IMGUI overlay:
    AnimViewerGUI gui = AnimViewerGUI(window.GetGLFWWindow());

    // Rendering Loop
    while (!window.ShouldClose()) {
        
        // TODO: move this into a "renderer" class
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
		
        // draw GUI
        gui.DrawAnimViewerGUI();

        window.SwapBuffersAndPollEvents();
    }

    window.Terminate();
    return EXIT_SUCCESS;
}
