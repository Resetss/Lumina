#pragma once

#include <glm/glm.hpp>

#include "../OpenGL/ShaderProgram.h"
#include "../OpenGL/VertexAttributes.h"
#include "../OpenGL/VertexArray.h"
#include "../OpenGL/ShaderProgram.h"
#include "../OpenGL/ShaderProgram.h"

#include "Camera.h"
#include "Transform.h"

#include <optional>
#include <string>
#include <vector>

struct MeshData
{
    float* vertices; 
    float* normals; 
    unsigned int* indices;
    uint32_t vertexCount;
    uint32_t indicesCount;
    Transform transform; 
};

class Mesh 
{
public:
    Mesh(MeshData& data);
    Mesh(const Mesh& other);
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(const Mesh& other);

    ~Mesh() = default; 

    void Destroy();

    Transform& GetTransform() { return m_Transform; };

    void Draw(GL::ShaderProgram& shader);
private:
    Transform m_Transform;

    GL::VertexAttributes m_VertexAttributes; 
    GL::VertexArray m_VertexArrays; 
};