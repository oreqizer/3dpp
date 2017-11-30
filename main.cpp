#include <GL/glew.h>

#include "src/display.h"
#include "src/mesh.h"
#include "src/shader.h"

// Make configs:
//   brew install cmake
//   cmake -H. -Bbuild
// Compile
//   cmake --build build
int main() {
    // A mock mesh data, a triangle
    Vertex vertices[] = {
        Vertex(glm::vec3(-0.5, -0.5, 0)),
        Vertex(glm::vec3(0, 0.5, 0)),
        Vertex(glm::vec3(0.5, -0.5, 0)),
    };

    Display display(800, 600, "Yolo");

    Shader shader("res/shaderBasic");
    Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

    while (!display.IsClosed()) {
        display.Clear(1.0f, 0.0f, 0.0f, 1.0f);
        mesh.Draw();
        shader.Bind();
        display.Update();
    }

    return 0;
}
