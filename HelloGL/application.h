#pragma once

#include "camera.h"
#include "resource_manager.h"
#include "2d_sprite_renderer.h"
#include "renderer/renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "cube.h"
#include "gui.h"
#include "terrain.h"
#include "quad.h"


#include "examples/scene.h"
#include "examples/postProcessing/post_processing_scene.h"
#include "examples/PerlinNoise/perlin_noise.h"


class Application
{
public:
	enum class State
	{
		MENU,
		SCENE
	};


public:
	bool m_keys[1024];
	unsigned int m_width, m_height;
	State m_state;
	bool drag{ false };

	std::unique_ptr<Scene> m_scene;

	////Window/gui stuff
	GLFWwindow* m_window; //TODO figure out how to use smart pointers...
	std::unique_ptr<GUI> m_gui;


	Application(unsigned int width, unsigned int height);
	~Application() { glfwDestroyWindow(m_window); };

	void init(GLFWwindow* window);
	void ProcessInput(float dt, float dx, float dy);
	void Update(float dt);
	void Render();
	 
	//Ensure that we cleanup anything that relies on glfw before glfw itself gets cleaned up
	void Cleanup();

};