#include "Shader.h"
#include "util.h"

//compilation checking
int success;
char infoLog[512];

void CompilationCheck_Shader(unsigned int const& shader, char const* ErrorMessage)
{
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << ErrorMessage << infoLog << std::endl;
	}
}

void CompilationCheck_Program(unsigned int const& program, char const* ErrorMessage)
{
	glGetProgramiv(program, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(program, 512, NULL, infoLog);
		std::cout << ErrorMessage << infoLog << std::endl;
	}
}

unsigned int CreateVertexShader(const char* shaderSource)
{
	unsigned int output = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(output, 1, &shaderSource, NULL);

	glCompileShader(output);
	//check for compilation was successful
	CompilationCheck_Shader(output, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");

	return output;
}

unsigned int CreateFragmentShader(const char* shaderSource)
{
	unsigned int output = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(output, 1, &shaderSource, NULL);

	glCompileShader(output);
	//check for compilation was successful
	CompilationCheck_Shader(output, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");

	return output;
}

unsigned int CreateShaderProgram(unsigned int const& vertexShader, unsigned int const& fragmentShader)
{
	unsigned int output = glCreateProgram();
	
	// Attach vertex shader to the shader program
	glAttachShader(output, vertexShader);
	// Attach fragment shader to the shader program
	glAttachShader(output, fragmentShader);

	glLinkProgram(output);
	//check for compilation was successful
	CompilationCheck_Program(output, "ERROR::SHADER PROGRAM::COMPILATION FAILED\n");

	return output;
}

void RenderTriangle(unsigned int const& shaderProgram, unsigned int const& VAO)
{
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void RenderRec(unsigned int const& shaderProgram, unsigned int const& VAO)
{
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
