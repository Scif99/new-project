#pragma once

#include <memory>
#include "../renderer/renderer.h"
#include "../camera.h"
#include "../cube.h"
#include "../terrain.h"
#include "../quad.h"
#include "../scene.h"
#include "../light.h"
#include "../gui.h"
#include "perlin_noise_gui.h"


class PerlinNoiseScene : public Scene
{
public:
	GLFWwindow& m_window;

	GLShader m_shader;

	//Camera m_camera;
	TerrainMesh m_perlin_mesh;
	
	PerlinGui m_gui;

public:
	~PerlinNoiseScene() { m_gui.Cleanup(); }
	PerlinNoiseScene(GLFWwindow* window);
	void ProcessInput(float dt, float dx, float dy) override;
	void Update(float dt) override;
	void Render() override;

};