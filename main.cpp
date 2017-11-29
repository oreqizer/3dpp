#include <GL/glew.h>

#include "src/display.h"

// Make configs:
//   brew install cmake
//   cmake -H. -Bbuild
// Compile
//   cmake --build build -- -j3
int main() {
    Display display(800, 600, "Yolo");

    while (!display.IsClosed()) {
        display.Clear(1.0f, 0.0f, 0.0f, 1.0f);
        display.Update();
    }

    return 0;
}
