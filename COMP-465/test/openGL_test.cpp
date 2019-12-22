#include <cstdio>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "common/shader.hpp"

int main(void)
{
	// initialize GLFW
	glewExperimental = true;
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}
	
	glfwWindowHint(GLFW_SAMPLES, 4);								// 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);					// OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);			// For MacOS
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);	// dont use old openGL

	// Open a window and create its OpenGL context
	GLFWwindow* window;
	window = glfwCreateWindow(1024, 768, "floating_window", NULL, NULL);
	if (window == NULL)
	{
		fprintf(stderr, "Failed to open GLFW window.");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);		// initialize GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// create Vertex Array Object (VAO) and set it as the current one
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// triangle shape points + colors
	float verticies[] =
	{
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,
		0.0f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f
	};

	// Create one, and only one, buffer for the triangle
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	// Create and Compile Shaders
	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader",
			"SimpleFragmentShader.fragmentshader");

	// Loop to keep window open and capture inputs
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	do
	{
		// clear screen, should prevent flickering
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);

		// draw the triangle
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);

		// swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(window) == 0);

	return 0;
}
