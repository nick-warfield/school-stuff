#include <filesystem>
#include <iostream>
#include <string>

#include <glad/glad.h>		// glad needs to go before all other openGL headers
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../include/Shader.hpp"
#include "../include/Camera.hpp"
#include "../include/Model.hpp"

void mouse_callback(GLFWwindow*, double, double);
void scroll_callback(GLFWwindow*, double, double);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
GLFWwindow* init(void);

const uint HEIGHT = 600, WIDTH = 800;
const std::string texPath = "crate.jpg";

Camera cam(glm::vec3(0.0f, 0.0f, -3.0f));
float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f, lastFrame = 0.0f;

int main(void)
{
	GLFWwindow* window = init();
	if (window == NULL) { return -1; }

	Shader shader("light.vs", "light.fs");
	Model model(std::filesystem::absolute("./plant.obj"));

	shader.SetInt("material.diffuse", 0);
	shader.SetInt("material.specular", 1);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		// draw stuff
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Use();
		shader.SetVec3("light.direction", -0.2f, -1.0f, -0.3f);
		shader.SetVec3("viewPos", cam.Position());

		shader.SetVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		shader.SetVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		shader.SetVec3("light.specular", 1.0f, 1.0f, 1.0f);

		shader.SetFloat("material.shininess", 32.0f);

		glm::mat4 view = cam.GetViewMatrix();
		glm::mat4 projection = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -15.0f));
		projection = glm::perspective(glm::radians(45.0f),
				(float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);

		shader.SetMat4("view", view);
		shader.SetMat4("projection", projection);

		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::translate(
				modelMatrix,
				glm::vec3(0.0f, -1.75f, 0.0f));
		modelMatrix = glm::scale(
				modelMatrix,
				glm::vec3(0.1f, 0.1f, 0.1f));

		shader.SetMat4("model", modelMatrix);
		model.draw(shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cam.Move(cam.Front(), 3 * deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cam.Move(-cam.Right(), 3 * deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cam.Move(-cam.Front(), 3 * deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cam.Move(cam.Right(), 3 * deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		cam.Move(cam.Up(), 3 * deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		cam.Move(-cam.Up(), 3 * deltaTime);
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    cam.MouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    cam.Zoom(yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GLFWwindow* init(void)
{
	// Instantiate GLFW Window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create Window Object
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "floating_window", NULL, NULL);
	if (window == NULL)
	{
		std::cerr << "Failed to create GLFW window\n";
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Initialize GLAD
	if ( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) )
	{
		std::cerr << "Failed ot initialize GLAD\n";
		return NULL;
	}

	glEnable(GL_DEPTH_TEST);

	// set and adjust viewport
	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return window;
}
