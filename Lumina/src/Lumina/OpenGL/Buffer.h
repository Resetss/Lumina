#ifndef BUFFER_H
#define BUFFER_H

#include <string>
#include <glad/glad.h>

namespace GL
{
    class Buffer
    {
    public:
        // Constructor: Initializes the buffer object and sets default values for member variables.
        Buffer();

        // Destructor: Ensures proper cleanup by deleting the OpenGL buffer if it has been created.
        ~Buffer();

        // Copy constructor: Creates a new buffer object as a copy of another, potentially duplicating OpenGL state.
        Buffer(const Buffer& other);

        // Move constructor: Transfers ownership of an existing buffer's resources to a new instance.
        Buffer(Buffer&& other) noexcept;

        // Copy assignment operator: Copies the buffer's data and OpenGL state from another instance.
        Buffer& operator=(const Buffer& other);

        // Initializes the OpenGL buffer object, generating a new buffer ID.
        void Init();

        // Deletes the OpenGL buffer, freeing its associated GPU memory.
        void Delete();

        // Binds the buffer object to the appropriate OpenGL target (e.g., GL_ARRAY_BUFFER).
        void Bind() const;

        // Unbinds the currently bound buffer from the target.
        void Unbind() const;

        // Retrieves the buffer's name, typically used for identification or debugging purposes.
        std::string GetBufferName() const { return m_Name; }

        // Retrieves the stride of the data in the buffer (e.g., the size of each vertex attribute).
        unsigned int GetStride() const { return m_Stride; }

        // Retrieves the number of elements stored in the buffer.
        unsigned int GetCount() const { return m_Count; }

        // Retrieves the OpenGL ID of the buffer, which uniquely identifies it within the GPU.
        unsigned int GetID() const { return m_ID; }

        // Uploads data to the GPU buffer. 
        // - `type`: Specifies the buffer type (e.g., GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER).
        // - `data`: Pointer to the buffer data to upload.
        // - `count`: Number of elements in the data array.
        // - `stride`: Size (in bytes) of a single data element.
        // - `usage`: OpenGL usage hint (e.g., GL_STATIC_DRAW, GL_DYNAMIC_DRAW).
        void SetData(GLuint type, const void* data, int count, int stride, GLenum usage = GL_STATIC_DRAW);

    private:
        std::string m_Name;    // Optional identifier for the buffer.
        GLuint m_Type;         // Type of buffer (e.g., GL_ARRAY_BUFFER).
        int m_Count;           // Number of elements stored in the buffer.
        int m_Stride;          // Size of a single element in bytes.
        GLuint m_ID;           // OpenGL identifier for the buffer.
    };
}

#endif