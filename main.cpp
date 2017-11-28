#include <GL/glew.h>
#include "src/display.h"

// Make configs:
//   brew install cmake
//   cmake -H. -Bbuild
// Compile
//   cmake --build build -- -j3
int main() {
    Display display(800, 600, "Yolo");
    return 0;
}
