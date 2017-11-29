#include <GL/glew.h>

#include "src/display.h"
#include "src/shader.h"

// Make configs:
//   brew install cmake
//   cmake -H. -Bbuild
// Compile
//   cmake --build build
int main() {
    Display display(800, 600, "Yolo");

    Shader shader("res/shaderBasic");

    while (!display.IsClosed()) {
        display.Clear(1.0f, 0.0f, 0.0f, 1.0f);
        shader.Bind();
        display.Update();
    }

    return 0;
}
