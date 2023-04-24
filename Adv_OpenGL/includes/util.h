#ifndef UTIL_H
#define UTIL_H

//OpenGL incl
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// C++ incl
#include <iostream>

void CompilationCheck_Shader	(unsigned int const& shader, char const* ErrorMessage);
void CompilationCheck_Program	(unsigned int const& program, char const* ErrorMessage);

unsigned int CreateVertexShader		(const char* shaderSource);
unsigned int CreateFragmentShader	(const char* shaderSource);
unsigned int CreateShaderProgram	(unsigned int const& vertexShader, unsigned int const& fragmentShader);

void RenderTriangle	(unsigned int const& shaderProgram, unsigned int const& VAO);
void RenderRec		(unsigned int const& shaderProgram, unsigned int const& VAO);

#endif