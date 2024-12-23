#include "Cube.h"

Cube::Cube()
{
    InitializeGeometry();
}

void Cube::InitializeGeometry()
{
    CubeData cubeData;

    m_Attributes.AddBuffer("a_Position", 0, cubeData.positions.data(), cubeData.positions.size(), 3);
    m_Attributes.AddBuffer("a_Normal", 1, cubeData.normals.data(), cubeData.normals.size(), 3);
    m_Attributes.AddBuffer("a_TexCoord", 2, cubeData.texCoords.data(), cubeData.texCoords.size(), 2);
    m_Attributes.AddBuffer("a_Transform", 3, nullptr, GL_FLOAT, sizeof(glm::mat4), 1);
    m_Attributes.AddIndices(cubeData.indices.data(), cubeData.indices.size());

    m_VertexArray.ApplyAttributes(m_Attributes); 

    m_Texture.SetSlot(1);
    m_Texture.SetData("res/texture/dirt.jpg");
}

void Cube::Draw(GL::ShaderProgram& shader, std::vector<glm::mat4>& instanceTransforms)
{
    m_Attributes.UpdateBuffer(3, instanceTransforms.data(), instanceTransforms.size(), sizeof(glm::mat4));

    m_VertexArray.Bind();
    
    m_Texture.Bind();

    m_VertexArray.Bind();
    m_VertexArray.DrawInstanced(GL_TRIANGLES, instanceTransforms.size());
    m_VertexArray.Unbind();

    m_Texture.Unbind();
}