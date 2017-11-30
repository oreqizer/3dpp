#include "mesh.h"

Mesh::Mesh(Vertex* vertices, unsigned int count) {
    m_drawCount = count;

    glGenVertexArrays(1, &m_vertexArrayObject);

    // Any operations on vertex arrays will be done on this one
    glBindVertexArray(m_vertexArrayObject);

    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

    // Divides the data to attributes.
    // For example, if one vertex would contain a position and a color,
    // It would tell OpenGL to look at the sequential data like:
    // [{position,color}, {positon,color} ...]
    //
    // This tells it that we have a sequential data
    // and it doesn't it need to do anything fancy.
    glEnableVertexAttribArray(0);
    // 3, GL_FLOAT -> glm::vec3. Zeros are offset
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // No longer affect the 'm_vertexArrayObject' via operations
    glBindVertexArray(0);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw() {
    glBindVertexArray(m_vertexArrayObject);

    glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

    glBindVertexArray(0);
}
