#pragma once
#include"Particle.h"
#include"Time.h"
#include"SpatialHash.h"
#include"PI.h"
#include <iostream>
#include <KHR/khrplatform.h>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
class FACADE
{
private:

public:
	void INITOPENGL_(int max_version, int lowest_version)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, max_version);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, lowest_version);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void CreateWindow(int width, int height,std::string label_name)
	{
		;
	}
};

