#include "stb_image.h"
#include "util.h"

#include "camera.h"
#include "Shader.h"

void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadTexture(char const* path);

// settings
const unsigned int SCR_WIDTH	= 800;
const unsigned int SCR_HEIGHT	= 600;

// camera
camera mainCam(glm::vec3(0.f, 0.f, 6.f),
			   glm::vec3(0.f, 1.f, 0.f),
			   400.f, 300.f, -90.f, 0.f, 45.f);

// dtime
float deltaTime = 0.f, lastFrame = 0.f;

// lighting
glm::vec3 lightPos(1.2f, 1.f, 2.f);

#pragma region 5.8 Exercise

//// 5.8 Exercise 1: 2 triangles next to each other
//float vertices[] = {
//	-0.5f, -0.5f, 0.f,
//	-0.25f, 0.5f, 0.f,
//	 0.f,  -0.5f, 0.f,
//
//	 0.5f, -0.5f, 0.f,
//	 0.25f, 0.5f, 0.f,
//	 0.f,  -0.5f, 0.f,
//};
//
//// 5.8 Exercise 2: 2 triangles using two different VAOs and VBOs
//float vertices_1[] = {
//	-0.5f, -0.5f, 0.f,
//	-0.25f, 0.5f, 0.f,
//	 0.f,  -0.5f, 0.f
//};
//float vertices_2[] = {
//	 0.5f, -0.5f, 0.f,
//	 0.25f, 0.5f, 0.f,
//	 0.f,  -0.5f, 0.f
//};

#pragma endregion

// rendering a rectangle
float vertices_rec[] = {
	// positions        // colors       // texture coords
	 0.5f,  0.5f, 0.f,  1.f, 0.f, 0.f,  1.f, 1.f,	// top right
	 0.5f, -0.5f, 0.f,  0.f, 1.f, 0.f,  1.f, 0.f,	// bottom right
	-0.5f, -0.5f, 0.f,  0.f, 0.f, 1.f,  0.f, 0.f,	// bottom left
	-0.5f,  0.5f, 0.f,  1.f, 1.f, 0.f,  0.f, 1.f	// top left
};

unsigned int indices_rec[] = {
	0, 1, 3, //first triangle
	1, 2, 3  //second triangle
};

// 3D cube
float vertices_cube[] = {
	// positions          // normals            // texture coords
	-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

int main()
{
#pragma region SYSTEM INIT

	// ------------------------------
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// ------------------------------
	// create a window object
	// ------------------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//allow user to resize window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Assign mouse input function
	glfwSetCursorPosCallback(window, mouse_callback);

	// Assign scroll input function
	glfwSetScrollCallback(window, scroll_callback);

	// Disable cursor in the window
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// ------------------------------
	// init GLAD
	// ------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Enable OpenGL z-axis depth setting
	glEnable(GL_DEPTH_TEST);

#pragma endregion



	// ------------------------------------
	// build and compile our shader program
	// ------------------------------------
	//Shader sTexture("./shaders/shader.vs", "./shaders/texture_multi.fs");
	Shader sLight("./shaders/shader_light.vs", "./shaders/light.fs");
	Shader sLightSource("./shaders/shader_light.vs", "./shaders/lightSource.fs");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	//vertex array object, vertex buffer object, element buffer obj
	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// -------------------------------------------------------------------------------
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_cube), vertices_cube, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_rec), indices_rec, GL_STATIC_DRAW);

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
	// -------------------------------------------------------------------------------


	// -------------------------------------------------------------------------------
	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);

	glBindVertexArray(lightCubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// -------------------------------------------------------------------------------

#pragma region load texture

	// Load textures
	// ------------------------------------------------------------------
	unsigned int diffuseMap = loadTexture("texture/wooden_container.png");
	unsigned int specularMap = loadTexture("texture/wooden_container_specular.png");
	unsigned int specularMap_r = loadTexture("texture/wooden_container_specular_real.png");
	unsigned int emissionMap = loadTexture("texture/matrix.jpg");

#pragma endregion



	//rendering loop
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Input
		// -------------------------------------------------------------------------------
		processInput(window);



		// Render
		// -------------------------------------------------------------------------------
		//creates a solid fill in the window
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// -------------------------------------------------------------------------------
		// math stuff with camera
		glm::mat4 model = glm::mat4(1.f);
		glm::mat4 view = glm::mat4(1.f);
		glm::mat4 projection = glm::mat4(1.f);

		projection = glm::perspective(glm::radians(mainCam.zoom), 800.f / 600.f, 0.1f, 100.f);
		view = glm::lookAt(mainCam.Pos, mainCam.Pos + mainCam.Front, mainCam.Up);
		// -------------------------------------------------------------------------------


		// -------------------------------------------------------------------------------
		// render light source
		sLightSource.use();

		sLightSource.setMat4("projection", projection);
		sLightSource.setMat4("view", view);

		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		sLightSource.setMat4("model", model);

		glBindVertexArray(lightCubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// -------------------------------------------------------------------------------


		// -------------------------------------------------------------------------------
		// Render Cube
		sLight.use();
		sLight.SetVec3("light.position", lightPos);
		sLight.SetVec3("viewPos", mainCam.Pos);

		// set light properties
		sLight.SetVec3("light.ambient", { 0.2f, 0.2f, 0.2f });
		sLight.SetVec3("light.diffuse", { 0.5f, 0.5f, 0.5f });
		sLight.SetVec3("light.specular", { 1.f, 1.f, 1.f });

		// set material properties
		sLight.setInt("material.diffuse", 0);
		sLight.setInt("material.specular", 1);
		sLight.setFloat("material.shininess", 64.f);
		sLight.setInt("material.emission", 2);

		// view/projection transformations
		sLight.setMat4("projection", projection);
		sLight.setMat4("view", view);

		// world transformation
		model = glm::mat4(1.f);
		sLight.setMat4("model", model);

		// bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, emissionMap);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// -------------------------------------------------------------------------------



		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightCubeVAO);

	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);

	glDeleteProgram(sLight.ID);
	glDeleteProgram(sLightSource.ID);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	// Exit
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	mainCam.cameraMovement(window, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	mainCam.mouse_input(window, xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	mainCam.scroll_input(window, xoffset, yoffset);
}

unsigned int loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);

	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
