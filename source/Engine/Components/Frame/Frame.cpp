#include "Frame.h"
#include <iostream>

Frame::Frame()
{
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);

	const GLFWvidmode * m = glfwGetVideoMode(glfwGetPrimaryMonitor());

	width = m->width;
	height = m->height;

	window = glfwCreateWindow(width,height, "Game", nullptr, nullptr);
	glfwMakeContextCurrent(window);
//	glfwSetKeyCallback(window,key_callback);

	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	glewInit();
	// Define the viewport dimensions
	glViewport(0, 0, width, height);
}

Frame::~Frame()
{
	glfwTerminate();
	glfwMakeContextCurrent(nullptr);
	glfwDestroyWindow(window);
}

GLFWwindow * Frame::getWindow() const
{
	return window;
}

void Frame::setTitle(const char* new_title)
{
	glfwSetWindowTitle(window, new_title);
}

 unsigned Frame::getWidth() const
{
	return width;
}

unsigned Frame::getHeight() const
{
	return  height;
}
