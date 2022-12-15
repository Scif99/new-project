 #pragma once

#include <memory>
#include "../renderer/renderer.h"
#include "../camera.h"
#include "../cube.h"
#include "../terrain.h"
#include "../quad.h"


class Scene
{
public:
	Camera m_camera;
public:
	virtual void ProcessInput(float dt, float dx, float dy) =0;
	virtual void Update(float dx) =0;
	virtual void Render() =0;

	virtual ~Scene() {};

};
