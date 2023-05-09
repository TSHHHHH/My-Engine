#ifndef CAMERA_H
#define CAMERA_H

#include "util.h"

// Camera default settings
const float SPEED		=   5.f;
const float SENSITIVITY =   0.1f;
const float YAW			= -90.f;
const float PITCH		=   0.f;
const float ZOOM		=  45.f;

class camera
{
public:
	glm::vec3 Pos;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	// Global up
	glm::vec3 WorldUp;

	bool firstMouse;
	float lastX, lastY, yaw, pitch, zoom;
	float speed, sensitivity;

	camera(glm::vec3 const& _cameraPos, glm::vec3 const& _WorldUp,
		   float const& _lastX, float const& _lastY, float const& _yaw = YAW, float const& _pitch = PITCH, float const& _zoom = ZOOM,
		   float const& _speed = SPEED, float const& _sensitivity = SENSITIVITY)
	{
		Pos = _cameraPos;
		WorldUp = _WorldUp;

		firstMouse = true;

		lastX = _lastX;
		lastY = _lastY;
		yaw = _yaw;
		pitch = _pitch;
		zoom = _zoom;

		speed = _speed;
		sensitivity = _sensitivity;

		updateCameraVectors();
	}

	void cameraMovement(GLFWwindow* window, float const& deltaTime)
	{
		const float cameraVelocity = speed * deltaTime;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			Pos.x += cameraVelocity * Front.x;
			Pos.z += cameraVelocity * Front.z;
		}

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			Pos.x -= cameraVelocity * Front.x;
			Pos.z -= cameraVelocity * Front.z;
		}

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			Pos -= Right * cameraVelocity;
		}

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			Pos += Right * cameraVelocity;
		}

		// Vertical movement control
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			Pos.y += cameraVelocity;
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
		{
			Pos.y -= cameraVelocity;
		}
	}

	void mouse_input(GLFWwindow* window, double xpos, double ypos)
	{
		if (firstMouse)
		{
			lastX = (float)xpos;
			lastY = (float)ypos;
			firstMouse = false;
		}

		float xoffset = (float)xpos - lastX;
		float yoffset = lastY - (float)ypos;
		lastX = (float)xpos;
		lastY = (float)ypos;

		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw   += xoffset;
		pitch += yoffset;

		if (pitch > 89.f)
			pitch = 89.f;
		if (pitch < -89.f)
			pitch = -89.f;

		updateCameraVectors();
	}

	void scroll_input(GLFWwindow* window, double xoffset, double yoffset)
	{
		zoom -= (float)yoffset;

		if (zoom < 1.f)
			zoom = 1.f;
		if (zoom > 45.f)
			zoom = 45.f;
	}

private:
	void updateCameraVectors()
	{
		// calculate the new Front vector
		glm::vec3 direction;
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		Front = glm::normalize(direction);

		// also re-calculate the Right and Up vector
		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
};

#endif // !CAMERA_H