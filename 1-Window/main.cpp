#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main() {

	glfwInit();

	// Specifies the major version of OpenGL we are using.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

	// Specifies the minor version of OpenGL we are using.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// OpenGL Profile we want to use.
	// A Profile is like a package of functions.
	// There are only two packages.
	// Core -> All modern functions 
	// Compatability -> All modern/outdated functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creates the window with dimensions [width/height], name, fullscreen (bool), and ??
	GLFWwindow* window = glfwCreateWindow(800, 800, "Hi Sean", NULL, NULL);

	// Error checking if window fails
	if (window == NULL) {
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Make the window part of the current context.
	// Context -> [abstract] an object that holds the whole of OpenGL.
	glfwMakeContextCurrent(window);

	// Glad!!
	gladLoadGL();

	// Area of window we want OpenGL to render in.
	// Bottom left (0,0) to top right (800,800)
	glViewport(0, 0, 800, 800);

	// Teal normalize dec. rbg color
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	// Execute command!
	glClear(GL_COLOR_BUFFER_BIT);

	//Swap the back buffer to the front.
	glfwSwapBuffers(window);

	// Ends on condition the window should close.
	while (!glfwWindowShouldClose(window))
	{
		// Process all pooled events.
		// Such as window appearing, resizing...etc 
		// Otherwise it will just be unresponsive.
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}