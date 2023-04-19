#pragma once
//OpenGL incl
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// C++ incl
#include <iostream>

void CompilationCheck_Shader(unsigned int const& shader, char const* ErrorMessage);
void CompilationCheck_Program(unsigned int const& program, char const* ErrorMessage);

unsigned int CreateShaderProgram(unsigned int const& vertexShader, unsigned int const& fragmentShader);