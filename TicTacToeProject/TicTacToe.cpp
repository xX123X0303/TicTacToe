#include "TicTacToe.h"

TicTacToe::TicTacToe(int width, int height): width(width), height(height)
{
	cellW = (2.0f - (cols + 1) * gap) / cols;
	cellH = (2.0f - (rows + 1) * gap) / rows;

	reset();
}

void TicTacToe::Draw(Shader& shader, Quad& quad) 
{
	shader.Use();

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			float x = -1.0f + gap + c * (cellW + gap);
			float y =  1.0f - gap - r * (cellH + gap);

			if (board[r][c] == "Blue") shader.setVec3("Color", { 0.749f, 0.890f, 0.874f });
			else if (board[r][c] == "Red") shader.setVec3("Color", { 0.850f, 0.513f, 0.435f });
			else if (board[r][c] == "Green") shader.setVec3("Color", { 0.705f, 0.858f, 0.466f });
			else shader.setVec3("Color", { 0.070f, 0.141f, 0.219f });

			quad.Update(x, y, cellW, cellH);
			quad.Draw();
		}
	}
}


bool TicTacToe::OnClick(double mouseX, double mouseY)
{
	float x =  (mouseX / width) * 2.0f - 1.0f;
	float y = -(mouseY / height) * 2.0f + 1.0f;

	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			float cellX = -1.0f + gap + c * (cellW + gap);
			float cellY =  1.0f - gap - r * (cellH + gap);

			bool inside =
				x >= cellX && x <= cellX + cellW &&
				y <= cellY && y >= cellY - cellH;

			if (inside && board[r][c] == "")
			{
				board[r][c] = currentPlayer;
				currentPlayer = (currentPlayer == "Blue") ? "Red" : "Blue";
				return true;
			}
		}
	}
	return false;
}

std::string TicTacToe::checkWinner()
{
	if (!playing) return winner;
	
	for (int r = 0; r < rows; r++)
	{
		if (board[r][0] != "" &&
			board[r][0] == board[r][1] && 
			board[r][1] == board[r][2])
		{
			winner = board[r][0];
			board[r][0] = board[r][1] = board[r][2] = "Green";
			return winner;
		}
	}

	for (int c = 0; c < cols; c++)
	{
		if (board[0][c] != "" &&
			board[0][c] == board[1][c] &&
			board[1][c] == board[2][c])
		{
			winner = board[0][c];
			board[0][c] = board[1][c] = board[2][c] = "Green";
			return winner;
		}
	}

	if (board[0][0] != "" &&
		board[0][0] == board[1][1] &&
		board[1][1] == board[2][2])
	{
		winner = board[0][0];
		board[0][0] = board[1][1] = board[2][2] = "Green";
		return winner;
	}

	if (board[2][0] != "" &&
		board[2][0] == board[1][1] &&
		board[1][1] == board[0][2])
	{
		winner = board[1][1];
		board[2][0] = board[1][1] = board[0][2] = "Green";
		return winner;
	}
	return "";
}

void TicTacToe::Delete(Shader& shader, Quad& quad)
{
	quad.Delete();
	shader.Delete();
}

void TicTacToe::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

	if (playing)
	{
		static bool mouseWasPressed = false;
		bool mousePressed = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

		if (mousePressed && !mouseWasPressed)
		{
			double mx, my;
			glfwGetCursorPos(window, &mx, &my);

			if (OnClick(mx, my))
			{
				std::string title = std::string("Tic-Tac-Toe - ") + currentPlayer + " turn";
				glfwSetWindowTitle(window, title.c_str());
			}
		}

		mouseWasPressed = mousePressed;
	}

	if (!playing)
	{
		
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) 
		{
			reset();
			std::string title = std::string("Tic-Tac-Toe - ") + currentPlayer + " turn";
			glfwSetWindowTitle(window, title.c_str());
		}
	}
}

void TicTacToe::setPlaying(bool playing)
{
	this->playing = playing;
}

void TicTacToe::reset()
{
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < cols; c++)
			board[r][c] = "";

	currentPlayer = "Blue";
	winner = "";
	playing = true;


}
