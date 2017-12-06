#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <GL/glew.h>

#include "../lib/obj_loader.h"

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
    template <size_t N, size_t M>
    Mesh(Vertex (&vertices)[N], unsigned int (&indices)[M]);
    Mesh(const std::string& filename);
    virtual ~Mesh();

    void Draw();
protected:
private:
    enum {
        POSITION_VB,
        TEXCOORD_VB,
        INDEX_VB,

        // How many items are in the enum
        NUM_BUFFERS
    };

    void InitMesh(const IndexedModel& model);

    GLuint m_vertexArrayObject;
    GLuint m_vertexArrayBuffers[NUM_BUFFERS];
    unsigned int m_drawCount;
};

// Why teh impl is here:
// https://stackoverflow.com/a/8752879/4337281
template<size_t N, size_t M>
Mesh::Mesh(Vertex (&vertices)[N], unsigned int (&indices)[M]) {
    IndexedModel model;

    for (Vertex& vertex : vertices) {
        model.positions.push_back(*vertex.GetPos());
        model.texCoords.push_back(*vertex.GetTex());
    }

    for (unsigned int& indice : indices) {
        model.indices.push_back(indice);
    }

    InitMesh(model);
}

Mesh::Mesh(const std::string& filename) {
    IndexedModel model = OBJModel(filename).ToIndexedModel();
    InitMesh(model);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw() {
    glBindVertexArray(m_vertexArrayObject);

    glDrawElements(GL_TRIANGLES, m_drawCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Mesh::InitMesh(const IndexedModel& model) {
    m_drawCount = model.indices.size();

    glGenVertexArrays(1, &m_vertexArrayObject);

    // Any operations on vertex arrays will be done on this one
    glBindVertexArray(m_vertexArrayObject);
    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

    // POSTITION_VB vuffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

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
    glBufferData(GL_ARRAY_BUFFER, model.texCoords.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0); // Attribute 1: texcoord

    // INDEX_VB buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

    // glEnableVertexAttribArray(1);
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0); // Attribute 2: texcoord
    
    // No more work
    glBindVertexArray(0);
}

#endif // MESH_H
