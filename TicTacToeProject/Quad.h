#pragma once

#include <glad/glad.h>

class Quad
{
public:
	Quad();

	void Update(float x, float y, float w, float h);
	void Draw();
	void Delete();
private:
	GLuint VAO, VBO, EBO;
};