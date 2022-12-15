#pragma once

#include <memory>
#include "../renderer/renderer.h"
#include "../camera.h"
#include "../cube.h"
#include "../terrain.h"
#include "../quad.h"
#include "../scene.h"
#include "../light.h"

class PostProcessingScene : public Scene
{
public:
	GLFWwindow& m_window;

	GLShader m_container_shader;
	GLShader m_light_source_shader;
	GLShader m_frame_buffer_shader;

	GLTexture m_container_diffuse;
	GLTexture m_container_specular;
	GLTexture m_tiles;
	//Camera m_camera;

	Container m_container;
	LightCube m_light;
	TerrainQuad	m_terrain;

	//Framebuffer stuff
	Quad m_frame_quad;
	Framebuffer m_framebuffer;

public:
	PostProcessingScene(GLFWwindow* window);
	void ProcessInput(float dt, float dx, float dy) override;
	void Update(float dt) override;
	void Render() override;

};