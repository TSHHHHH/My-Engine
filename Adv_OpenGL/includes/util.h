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

// system related
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// rendering
void CompilationCheck_Shader	(unsigned int const& shader, char const* ErrorMessage);
void CompilationCheck_Program	(unsigned int const& program, char const* ErrorMessage);

unsigned int CreateVertexShader		(const char* shaderSource);
unsigned int CreateFragmentShader	(const char* shaderSource);
unsigned int CreateShaderProgram	(unsigned int const& vertexShader, unsigned int const& fragmentShader);

void RenderTriangle	(unsigned int const& shaderProgram, unsigned int const& VAO);
void RenderRec		(unsigned int const& shaderProgram, unsigned int const& VAO);

// camera
glm::mat4 my_lookAt(glm::vec3 const& pos, glm::vec3 const& target, glm::vec3 const& worldUp);

#endif