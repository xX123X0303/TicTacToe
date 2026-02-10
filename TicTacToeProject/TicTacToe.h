#pragma once

#include "Shader.h"
#include "Quad.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class TicTacToe
{
public:
	TicTacToe(int width, int height);

	void Draw(Shader& shader, Quad& quad);
	void processInput(GLFWwindow* window);
	bool OnClick(double mouseX, double mouseY);
	void setPlaying(bool playing);
	std::string checkWinner();
	void reset();

	void Delete(Shader& shader, Quad& quad);

private:
	int rows = 3;
	int cols = 3;
	int width, height;

	float gap = 0.05f;
	float cellW, cellH;

	std::string board[3][3];
	std::string currentPlayer;
	std::string winner;

	bool playing;

};