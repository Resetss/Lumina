#include <vector>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Lumina/Layer.h"

#include "Lumina/Utils/Timer.h"
#include "Lumina/Utils/FileReader.h"

#include "Lumina/OpenGL/GLUtils.h"
#include "Lumina/OpenGL/ShaderProgram.h"
#include "Lumina/OpenGL/FrameBuffer.h"
#include "Lumina/OpenGL/Texture.h"
#include "Lumina/OpenGL/VertexAttributes.h"
#include "Lumina/OpenGL/VertexArray.h"

#include "Lumina/Renderer/OrthographicCamera.h"

// Client
#include "TileEditor.h"
#include "TileRenderer.h"

class Tiles : public Lumina::Layer
{
public:
    Tiles()
    {
        m_Camera.SetPosition(glm::vec3(10.0f, 10.0f, 25.0f));

        glm::vec2 viewportSize = m_TileRenderer.GetViewportSize();
        m_Camera.SetProjectionMatrix(-viewportSize.x / m_Zoom, viewportSize.x / m_Zoom,
            -viewportSize.y / m_Zoom, viewportSize.y / m_Zoom,
            0.1f, 100.0f);
    }

    virtual void OnUpdate(float timestep) override
    {
        m_Camera.HandleKeyInput(0.1f);

        float elapsedTime = m_FrameTimer.Elapsed();
        m_FPS = 1.0f / elapsedTime;
        m_FrameTimer.Reset();
    }

    virtual void OnUIRender() override
    {
        m_TileEditor.Render(); 

        m_Camera.HandleMouseInput(0.1f);
        glm::vec2 viewportSize = m_TileRenderer.GetViewportSize();
        
        m_Camera.SetProjectionMatrix(-viewportSize.x / m_Zoom, viewportSize.x / m_Zoom,
            -viewportSize.y / m_Zoom, viewportSize.y / m_Zoom,
            0.1f, 100.0f);

        m_TileRenderer.Render(m_Camera, m_TileEditor.GetMatrices(), m_TileEditor.GetOffsets(), m_ShaderProgram);

        ImGui::Begin("FPS Counter");
        ImGui::Text("FPS: %.1f", m_FPS);
        ImGui::End(); 
    }

    virtual void OnAttach() override
    {   
        std::string vertex = Lumina::ReadFile("res/shaders/world.vert");
        std::string fragment = Lumina::ReadFile("res/shaders/world.frag");
        m_ShaderProgram.SetSource(vertex, fragment); 
    }

    virtual void OnDetach() override
    {
        m_TileEditor.Shutdown(); 
        m_ShaderProgram.Destroy(); 
    }
private:
    TileEditor m_TileEditor; 
    TileRenderer m_TileRenderer;

    float m_Zoom = 90.0f;

    Lumina::Timer m_FrameTimer;
    float m_FPS = 0;
    
    OrthographicCamera m_Camera;

    GL::ShaderProgram m_ShaderProgram; 
};