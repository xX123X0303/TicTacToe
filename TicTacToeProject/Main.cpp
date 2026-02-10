#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "TicTacToe.h"

const int width = 900;
const int height = 900;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, TicTacToe& game);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Tic-Tac-Toe - Blue turn", NULL, NULL);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to load GLAD function" << std::endl;
		return -1;
	}

	Shader shader("default.vert", "default.frag");
	Quad quad;

	TicTacToe game(width, height);

	while (!glfwWindowShouldClose(window))
	{
		game.processInput(window);

		std::string w = game.checkWinner();
		if (w != "")
		{
			glfwSetWindowTitle(window, (w + " win!   Press 'R' to reset." ).c_str());
			game.setPlaying(false);
		}

		glClearColor(0.039f, 0.066f, 0.094f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		game.Draw(shader, quad);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	game.Delete(shader, quad);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}