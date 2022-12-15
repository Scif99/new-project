#include "camera.h"

#include <iostream>

inline const unsigned int SCREEN_WIDTH = 800;
inline const unsigned int SCREEN_HEIGHT = 600;

//Note forward, up should be orthogonal
Camera::Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up)
    : m_position{ pos }, m_forward{ glm::normalize(target - m_position) }, m_up{ glm::normalize(up) }, m_right{ glm::normalize(glm::cross(m_forward, m_up)) },
     lastX{SCREEN_WIDTH/2}, lastY{SCREEN_HEIGHT/2}, firstMouse{true}
{
    WORLD_UP = m_up;
}


void Camera::ProcessKeyboardInput(GLFWwindow* window, float dt)
{
    const float speed{ 2.5f * dt };

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_position += speed * m_forward;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_position -= speed * m_forward;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_position -= speed * m_right;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_position += speed * m_right;

    //m_position.y = 0.f;

}


void Camera::ProcessMouseInput(GLFWwindow* window, float dx, float dy)
{

    dx *= sensitivity;
    dy *= sensitivity;

    yaw += dx;
    pitch += dy;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
}

void Camera::Update()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    m_forward = glm::normalize(direction);

    // also re-calculate the Right and Up vector
    // 
    m_right = glm::normalize(glm::cross(m_forward, WORLD_UP));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    m_up = glm::normalize(glm::cross(m_right, m_forward));

    m_view = glm::lookAt(m_position, m_position + m_forward, m_up);
}