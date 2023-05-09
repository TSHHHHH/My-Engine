#include "Shader.h"
#include "util.h"

//compilation checking
int success;
char infoLog[512];

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

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

glm::mat4 my_lookAt(glm::vec3 const& pos, glm::vec3 const& target, glm::vec3 const& worldUp)
{
	// 1. position = known
	// 2. calculate camera direction
	glm::vec3 zaxis = glm::normalize(pos - target);
	// 3. get positive right axit
	glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(worldUp), zaxis));
	// 4. calculate camera up
	glm::vec3 yaxis = glm::normalize(glm::cross(zaxis, xaxis));

	// Create translation and rotation matrix
	// In glm we access elements as mat[col][row] due to column-major layout
	glm::mat4 trans = glm::mat4(1.f);
	trans[3][0] = -pos.x;
	trans[3][1] = -pos.y;
	trans[3][2] = -pos.z;

	glm::mat4 rot = glm::mat4(1.f);
	rot[0][0] = xaxis.x;
	rot[1][0] = xaxis.y;
	rot[2][0] = xaxis.z;

	rot[0][1] = yaxis.x;
	rot[1][1] = yaxis.y;
	rot[2][1] = yaxis.z;

	rot[0][2] = zaxis.x;
	rot[1][2] = zaxis.y;
	rot[2][2] = zaxis.z;

	return rot * trans;
}
