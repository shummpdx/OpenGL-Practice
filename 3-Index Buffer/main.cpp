#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

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
	GLFWwindow* window = glfwCreateWindow(800, 800, "Hi Triangllie", NULL, NULL);

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

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,    // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,     // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,   // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,  // Inner right
		0.0f,  -0.5f * float(sqrt(3)) / 3, 0.0f     // Inner down
	};

	GLuint indices[] = {
		0, 3, 5,
		3, 2, 4,
		5, 4, 1
	};

	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Ends on condition the window should close.
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		// Process all pooled events.
		// Such as window appearing, resizing...etc 
		// Otherwise it will just be unresponsive.
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}