#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// OpenGL does not provide us with defaults for the vertex/fragment shaders. We'll have to 'write our own'
// Shaders will be discussed later.
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
"    FragColor = vec4(0.8f, 0.3f, 0.03f, 1.0f);\n"
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

	// GLfloat is more standardized. Safer. 
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,     // Left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,      // Right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f    // Center
	};

	// Creates the window with dimensions [width/height], name, fullscreen (bool), and ??
	GLFWwindow* window = glfwCreateWindow(800, 800, "Hi Triangle", NULL, NULL);

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

	// Shaders are an OpenGL object which are in the backgroun in memory.
	// We access them by references (aka value).
	
	// Create a value (aka reference) to store our vertex shader in.
	// glCreateShader returns a reference value. You should specify which type of shader you want.
	// We want a VERTEX shader.
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Reference value, 1 string for the whole shader, point to source code, blah blah blah write NULL)
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// We must complie it right now
	glCompileShader(vertexShader);

	// Same thing, only for fragment shader.
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// In order to actually use both of the shaders, we'll have to wrap themn up in a 'shaderProgram'
	GLuint shaderProgram = glCreateProgram();

	// Attachment
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Link (wrap them up)
	glLinkProgram(shaderProgram);

	// Delete shaders we've created since they are already in the program itself. 
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// We will begin to tell how OpenGL can interpret our vertices. 
	
	// Sending stuff from CPU -> GPU we want big batches = buffers.

	// Vertex buffer object = VBO
	// VBO is an array of references, but for now we'll just keep it like this.
	GLuint VAO, VBO;

	// 1 object, point to reference
	glGenVertexArrays(1, &VAO);

	// Binding: we make a certain object the current object. 
	// Whenever we execute a function that would modify that type of object, it modifies that current object (aka the binded object)

	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Teal normalize dec. rbg color
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	// Execute command!
	glClear(GL_COLOR_BUFFER_BIT);

	//Swap the back buffer to the front.
	glfwSwapBuffers(window);

	// Ends on condition the window should close.
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		// Process all pooled events.
		// Such as window appearing, resizing...etc 
		// Otherwise it will just be unresponsive.
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}