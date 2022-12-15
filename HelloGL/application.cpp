#include "application.h"

#include <memory>

    

Application::Application(unsigned int width, unsigned int height)
	:m_keys(), m_width{ width }, m_height{ height }, m_state{Application::State::MENU}
{

}

void Application::init(GLFWwindow* window)
{
    //Load scene
    //(scene can have stack-allocated members rather than pointers everywhere)
    m_window = window;
    //m_scene = std::make_unique<PostProcessingScene>(window);
    m_scene = std::make_unique<PerlinNoiseScene>(window);
}


void Application::ProcessInput(float dt, float dx, float dy)
{
    m_scene->ProcessInput(dt, dx, dy);
}

void Application::Update(float dt)
{
    m_scene->Update(dt);

}

void Application::Render()
{
    m_scene->Render();

}

void Application::Cleanup()
{
}
