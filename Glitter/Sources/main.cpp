// Local Headers
#include "glitter.hpp"
#include "Window.hpp"
#include "AnimViewerGUI.hpp"
#include "FbxLoader.hpp"
#include "IUpdatable.hpp"
#include <vector>

// TODO: move into a "renderer" class
#include "SimpleMesh.hpp"
#include "Camera.hpp"

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

    gui.SetFbxLoader(&fbxLoader);

    Camera testCamera{};
    testCamera.SetCameraAspect(window.GetAspectRatio());
    SimpleMesh testTriangle{};

    updatables.push_back(&fbxLoader);
    updatables.push_back(&testCamera);
    updatables.push_back(&testTriangle);

    // Rendering Loop
    while (!window.ShouldClose()) {
        // get time since last frame:
        float dt = window.GetDeltaTime();

        // process input

        // update state
        for (auto updateable : updatables)
        {
            updateable->Update(dt);
        }

        // process animation data

        // render models with animation data
		// TODO: move this into a "renderer" class
		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
        // draw GUI
        gui.DrawAnimViewerGUI();

        // draw models
        testTriangle.Draw(&testCamera);

        window.SwapBuffersAndPollEvents();
    }

    window.Terminate();
    return EXIT_SUCCESS;
}
