#include "util.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

const char* vertexShaderSource =
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const char* fragmentShaderSource_orange =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";

const char* fragmentShaderSource_yellow =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"  FragColor = vec4(1.0f, 1.0f, 0.f, 1.0f);\n"
	"}\0";

const char* fragmentShaderSource_darkRed =
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"  FragColor = vec4(0.8f, 0.f, 0.2f, 1.0f);\n"
	"}\0";

// 5.8 Exercise 1: 2 triangles next to each other
float vertices[] = {
	-0.5f, -0.5f, 0.f,
	-0.25f, 0.5f, 0.f,
	 0.f,  -0.5f, 0.f,

	 0.5f, -0.5f, 0.f,
	 0.25f, 0.5f, 0.f,
	 0.f,  -0.5f, 0.f,
};

// 5.8 Exercise 2: 2 triangles using two different VAOs and VBOs
float vertices_1[] = {
	-0.5f, -0.5f, 0.f,
	-0.25f, 0.5f, 0.f,
	 0.f,  -0.5f, 0.f
};
float vertices_2[] = {
	 0.5f, -0.5f, 0.f,
	 0.25f, 0.5f, 0.f,
	 0.f,  -0.5f, 0.f
};

// rendering a rectangle
float vertices_rec[] = {
	 0.5f,  0.5f, 0.f, // top right
	 0.5f, -0.5f, 0.f, // bottom right
	-0.5f, -0.5f, 0.f, // bottom left
	-0.5f,  0.5f, 0.f  // top left
};
unsigned int indices_rec[] = {
	0, 1, 3, //first triangle
	1, 2, 3  //second triangle
};

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//create a window object
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//create a default window
	glViewport(0, 0, 800, 600);
	//allow user to resize window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	


	// build and compile our shader program
	// ------------------------------------
	//vertex shader for shape
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//check for compilation was successful
	CompilationCheck_Shader(vertexShader, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");

	//fragment shader for color
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource_orange, NULL);
	glCompileShader(fragmentShader);
	//check for compilation was successful
	CompilationCheck_Shader(fragmentShader, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");

	unsigned int fragmentShader_yellow = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_yellow, 1, &fragmentShaderSource_yellow, NULL);
	glCompileShader(fragmentShader_yellow);
	//check for compilation was successful
	CompilationCheck_Shader(fragmentShader_yellow, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");

	unsigned int fragmentShader_darkRed = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_darkRed, 1, &fragmentShaderSource_darkRed, NULL);
	glCompileShader(fragmentShader_darkRed);
	//check for compilation was successful
	CompilationCheck_Shader(fragmentShader_darkRed, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");

	//shader progeam(s)
	unsigned int shaderProgram_orange = CreateShaderProgram(vertexShader, fragmentShader);
	unsigned int shaderProgram_yellow = CreateShaderProgram(vertexShader, fragmentShader_yellow);
	unsigned int shaderProgram_darkRed = CreateShaderProgram(vertexShader, fragmentShader_darkRed);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShader_yellow);
	glDeleteShader(fragmentShader_darkRed);



	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	//vertex array object, vertex buffer object
	unsigned int VAOs[3], VBOs[3];
	glGenVertexArrays(3, VAOs);
	glGenBuffers(3, VBOs);

	glBindVertexArray(VAOs[0]);
	//OpenGL has many types of buffer objects and the buffer type of a vertex buffer object is GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_2), vertices_2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAOs[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_rec), vertices_rec, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_rec), indices_rec, GL_STATIC_DRAW);



	//rendering loop
	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);

		//rendering
		//creates a solid fill in the window
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram_darkRed);
		glBindVertexArray(VAOs[2]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glUseProgram(shaderProgram_orange);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram_yellow);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);



		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(3, VAOs);
	glDeleteBuffers(3, VBOs);
	glDeleteProgram(shaderProgram_orange);
	glDeleteProgram(shaderProgram_yellow);
	glDeleteProgram(shaderProgram_darkRed);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
