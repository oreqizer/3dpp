#ifndef MESH_H
#define MESH_H

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

class Mesh {
public:
    template <size_t N> Mesh(Vertex (&vertices)[N]);
    virtual ~Mesh();

    void Draw();
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
