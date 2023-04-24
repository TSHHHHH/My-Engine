#include "Shader.h"
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

//const char* vertexShaderSource =
//	"#version 330 core\n"
//	"layout (location = 0) in vec3 aPos;\n"
//	"void main()\n"
//	"{\n"
//	"  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//	"}\0";

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

// triangle with more attributes
float vertices_colorfulTri[] = {
	// positions        // colors
	 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
	 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top
};

float texCoords[] = {
	0.f,  0.f,	// lower-left corner
	1.f,  0.f,	// lower-right corner
	0.5f, 1.f	// top-center corner
};

float vertices_tex[] = {
	// positions        // colors       // texture coords
	 0.5f,  0.5f, 0.f,  1.f, 0.f, 0.f,  1.f, 1.f,	// top right
	 0.5f, -0.5f, 0.f,  0.f, 1.f, 0.f,  1.f, 0.f,	// bottom right
	-0.5f, -0.5f, 0.f,  0.f, 0.f, 1.f,  0.f, 0.f,	// bottom left
	-0.5f,  0.5f, 0.f,  1.f, 1.f, 0.f,  0.f, 1.f	// top left
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
	Shader sTexture("./shaders/shader.vs", "./shaders/texture_multi.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	//vertex array object, vertex buffer object, element buffer obj
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_tex), vertices_tex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_rec), indices_rec, GL_STATIC_DRAW);

	// assign attributes base on vertex code
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	stbi_set_flip_vertically_on_load(true);



	// Load textures
	// ------------------------------------------------------------------
	unsigned int texture_1, texture_2;

	glGenTextures(1, &texture_1);
	glBindTexture(GL_TEXTURE_2D, texture_1);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("texture/opengl.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		//generate texture using the previously loaded image data
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glGenTextures(1, &texture_2);
	glBindTexture(GL_TEXTURE_2D, texture_2);

	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	data = stbi_load("texture/google.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		//generate texture using the previously loaded image data
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	sTexture.use();
	sTexture.setInt("ourTexture1", 0);
	sTexture.setInt("ourTexture2", 1);
	float alpha = 0.f;
	sTexture.setFloat("alpha", alpha);



	// math stuff
	// ------------------------------------------------------------------
	glm::mat4 trans = glm::mat4(1.f);
	trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.f));
	trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

	unsigned int transformLoc = glGetUniformLocation(sTexture.ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));



	//rendering loop
	while (!glfwWindowShouldClose(window))
	{
		// Input
		// -------------------------------------------------------------------------------
		processInput(window);

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			alpha += 0.01f;
			if (alpha >= 1.f)
			{
				alpha = 1.f;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			alpha -= 0.01f;
			if (alpha <= 0.f)
			{
				alpha = 0.f;
			}
		}
		sTexture.setFloat("alpha", alpha);



		// Render
		// -------------------------------------------------------------------------------
		//creates a solid fill in the window
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture_2);

		sTexture.use();
		glBindVertexArray(VAO);

		// first transformation
		// ---------------------
		glm::mat4 trans = glm::mat4(1.f);
		trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.f));

		unsigned int transformLoc = glGetUniformLocation(sTexture.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// second transformation
		// ---------------------
		trans = glm::mat4(1.0f); // reset it to identity matrix
		trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
		float scaleAmount = static_cast<float>(sin(glfwGetTime()));
		trans = glm::scale(trans, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &trans[0][0]); // this time take the matrix value array's first element as its memory pointer value

		// now with the uniform matrix being replaced with new transformations, draw it again.
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glDeleteProgram(sTexture.ID);

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
