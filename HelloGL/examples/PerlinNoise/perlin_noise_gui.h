#pragma once
#include "../gui.h"

class PerlinGui : public GUI
{
	//**WHAT IF WE WANT MULTIPLE IMGUI WINDOWS?**
	void CreateWindow()
	{

		ImGui::Begin("Perlin Noise");

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
};