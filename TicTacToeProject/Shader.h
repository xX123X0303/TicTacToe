#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

std::string get_file_contents(const char* filename);

class Shader
{
public:
	GLuint ID;
	Shader(const char* vertexFile, const char* fragmentFile);

	void Use();
	void Delete();

	void setVec3(const std::string& name, const glm::vec3& value) const;

private:
	void compileError(GLuint shader, std::string type);
};