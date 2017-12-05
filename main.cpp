#include <GL/glew.h>
#include <unistd.h>

#include "src/display.h"
#include "src/mesh.h"
#include "src/shader.h"
#include "src/texture.h"
#include "src/transform.h"

// Make configs:
//   brew install cmake
//   cmake -H. -Bbuild
// Compile
//   cmake --build build
int main() {
    // A mock mesh data, a triangle
    Vertex vertices[] = {
        Vertex(glm::vec3(-0.5, -0.5, 0.0), glm::vec2(1.0, 1.0)),
        Vertex(glm::vec3(0.0, 0.5, 0.0), glm::vec2(0.535, 0.0)),
        Vertex(glm::vec3(0.5, -0.5, 0.0), glm::vec2(0.0, 1.0)),
    };

    Display display(800, 600, "Yolo");

    Mesh mesh(vertices);
    Shader shader("res/shader.vert", "res/shader.frag");
    Texture texture("res/illuminati.png");
    Transform transform;

    float counter = 0.0f;

    // I don't know why I need 2 of them.
    // Silly 'nanosleep'
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 16000000L; // 16ms

    while (!display.IsClosed()) {
        display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

        transform.SetPos(glm::vec3(sinf(counter), 0.0f, 0.0f));
        transform.SetRot(glm::vec3(0.0f, 0.0f, counter));
        transform.SetScale(glm::vec3(cosf(counter), cosf(counter), cosf(counter)));

        mesh.Draw();
        texture.Bind(0);
        shader.Update(transform);
        shader.Bind();

        display.Update();
        counter += 0.1f;
        nanosleep(&tim, &tim2);
    }

    return 0;
}
