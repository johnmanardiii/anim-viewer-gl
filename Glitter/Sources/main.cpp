// Local Headers
#include "glitter.hpp"
#include "Window.hpp"
#include "AnimViewerGUI.hpp"
#include "FbxLoader.hpp"
#include "IUpdatable.hpp"
#include <vector>

int main() {
    // create list of updatable objects
    std::vector<IUpdatable*> updatables;

    Window window = Window(mWidth, mHeight);
    if (!window.IsValid())
    {
        return EXIT_FAILURE;
    }

    // initialize IMGUI overlay:
    AnimViewerGUI gui = AnimViewerGUI(window.GetGLFWWindow());

    // Launch the fbx loader thread
    FbxLoader fbxLoader{};
    updatables.push_back(&fbxLoader);

    // Rendering Loop
    while (!window.ShouldClose()) {
        // process input

        // update state
        for (auto updateable : updatables)
        {
            updateable->Update();
        }

        // process animation data

        // render models with animation data
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
