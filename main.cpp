#include <GL/glew.h>

#include "src/display.h"
#include "src/mesh.h"
#include "src/shader.h"
#include "src/texture.h"

// Make configs:
//   brew install cmake
//   cmake -H. -Bbuild
// Compile
//   cmake --build build
int main() {
    // A mock mesh data, a triangle
    Vertex vertices[] = {
        Vertex(glm::vec3(-0.5, -0.5, 0.0), glm::vec2(1.0, 1.0)),
        Vertex(glm::vec3(0.0, 0.5, 0.0), glm::vec2(0.5, 0.0)),
        Vertex(glm::vec3(0.5, -0.5, 0.0), glm::vec2(0.0, 1.0)),
    };

    Display display(800, 600, "Yolo");

    Mesh mesh(vertices);
    Shader shader("res/shaderBasic");
    Texture texture("res/illuminati.jpg");

    while (!display.IsClosed()) {
        display.Clear(1.0f, 0.0f, 0.0f, 1.0f);

        mesh.Draw();
        texture.Bind(0);
        shader.Bind();

        display.Update();
    }

    return 0;
}
