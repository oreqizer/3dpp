#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

class Vertex {
public:
    Vertex(const glm::vec3& pos, const glm::vec2& tex) {
        this->pos = pos;
        this->tex = tex;
    };

    inline glm::vec3* GetPos() { return &pos; }
    inline glm::vec2* GetTex() { return &tex; }
protected:
private:
    glm::vec3 pos;
    glm::vec2 tex;
};

// Why teh impl is here:
// https://stackoverflow.com/a/8752879/4337281
class Mesh {
public:
    template <size_t N>
    Mesh(Vertex (&vertices)[N]) {
        m_drawCount = N;
    
        glGenVertexArrays(1, &m_vertexArrayObject);
    
        // Any operations on vertex arrays will be done on this one
        glBindVertexArray(m_vertexArrayObject);
    
        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> texcoords;
    
        positions.reserve(N);
        texcoords.reserve(N);
    
        for (Vertex& vertex : vertices) {
            positions.push_back(*vertex.GetPos());
            texcoords.push_back(*vertex.GetTex());
        }
    
        glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
    
        // POSTITION_VB vuffer
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
        glBufferData(GL_ARRAY_BUFFER, N * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
    
        // Divides the data to attributes.
        // For example, if one vertex would contain a position and a color,
        // It would tell OpenGL to look at the sequential data like:
        // [{position,color}, {positon,color} ...]
        //
        // This tells it that we have a sequential data
        // and it doesn't it need to do anything fancy.
        glEnableVertexAttribArray(0);
        // 3, GL_FLOAT -> glm::vec3. Zeros are offset
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Attribute 0: position
    
        // TEXCOORD_VB buffer
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
        glBufferData(GL_ARRAY_BUFFER, N * sizeof(texcoords[0]), &texcoords[0], GL_STATIC_DRAW);
    
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Attribute 1: texcoord
        
        // No more work
        glBindVertexArray(0);
    };
    virtual ~Mesh() {
        glDeleteVertexArrays(1, &m_vertexArrayObject);
    };

    void Draw() {
        glBindVertexArray(m_vertexArrayObject);
    
        glDrawArrays(GL_TRIANGLES, 0, m_drawCount);
    
        glBindVertexArray(0);
    };
protected:
private:
    enum {
        POSITION_VB,
        TEXCOORD_VB,

        // How many items are in the enum
        NUM_BUFFERS
    };

    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_drawCount;
};

#endif // MESH_H
