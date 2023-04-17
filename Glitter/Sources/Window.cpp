#include "Window.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdio.h>

Window::Window(int mWidth, int mHeight)
{
	// Load GLFW and Create a Window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindow = glfwCreateWindow(mWidth, mHeight, "OpenGL", nullptr, nullptr);

	isValid = (glfwWindow != nullptr);

	// Create Context and Load OpenGL Functions
	glfwMakeContextCurrent(glfwWindow);

	// TODO: figure out where this line should go.
	gladLoadGL();
	fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));
}

Window::~Window()
{

}

GLFWwindow* Window::GetGLFWWindow()
{
	return glfwWindow;
}

bool Window::ShouldClose()
{
	return glfwWindowShouldClose(glfwWindow);
}

bool Window::IsValid()
{
	return isValid;
}

void Window::Terminate()
{
	glfwTerminate();
}

void Window::SwapBuffersAndPollEvents()
{
	glfwSwapBuffers(glfwWindow);
	glfwPollEvents();
}
