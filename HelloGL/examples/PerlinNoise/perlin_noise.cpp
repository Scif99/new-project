#include "perlin_noise.h"

inline const unsigned int SCREEN_WIDTH = 800;
inline const unsigned int SCREEN_HEIGHT = 600;

constexpr int MESH_VERTICES_X{ 64 };
constexpr int MESH_VERTICES_Z{ 64 };

PerlinNoiseScene::PerlinNoiseScene(GLFWwindow* window)
    :
    m_window{ *window },
    //Shaders
    //m_shader{ GLShader("shaders/LightSourceShader.vs", "shaders/LightSourceShader.fs") }
    m_shader{ GLShader("shaders/StripeShader.vs", "shaders/StripeShader.fs") },
    m_gui{window},
    //Entities
    m_perlin_mesh{ MESH_VERTICES_X, MESH_VERTICES_Z}
    //All other entities are constructed using default
{}

void PerlinNoiseScene::ProcessInput(float dt, float dx, float dy)
{
    m_camera.ProcessKeyboardInput(&m_window, dt);
    m_camera.ProcessMouseInput(&m_window, dx, dy);
}

void PerlinNoiseScene::Update(float dt)
{
    m_gui.CreateFrame();
    m_camera.Update();
}


void PerlinNoiseScene::Render()
{
    //**WHAT IF WE WANT MULTIPLE IMGUI WINDOWS?**

    static int t{ 128 };
    static float k{ 5.f };
    static float v{ 1.f };
    static float a{ 1.f };

    ImGui::Begin("Scene Menu");
    ImGui::SliderFloat("K", &k, 1.f, 10.f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::SliderFloat("Velocity", &v, 0.0f, 5.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::SliderFloat("Amp", &a, 0.0f, 5.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::SliderInt("Tesselation", &t, 2, 128);            // Edit 1 float using a slider from 0.0f to 1.0f

    
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();


    glClearColor(0.1f, 0.1f, 0.1f, 1.f); //state-setting
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //state-using
    glEnable(GL_DEPTH_TEST);

    //Projection & view don't change per object
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = m_camera.getView();

    //-------------------
    // WOODEN CONTAINER
    //---------------
    //Bind shader, pass uniforms
    m_shader.Use();
    m_shader.SetMat4("projection", projection);
    m_shader.SetMat4("view", view);


    m_shader.SetFloat("Time", (float)glfwGetTime());
    m_shader.SetFloat("K", k);
    m_shader.SetFloat("Velocity", v);
    m_shader.SetFloat("Amp", a);

    //Model
    m_perlin_mesh = TerrainMesh(t, t);
    glm::mat4 model = glm::mat4(1.f);
    model = glm::scale(model, glm::vec3(1.f, 1.f, 3.f));
    m_shader.SetMat4("model", model);
    m_perlin_mesh.Draw();

    m_gui.Render();
}