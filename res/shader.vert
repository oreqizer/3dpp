#version 120

attribute vec3 position;
attribute vec2 texcoord;

varying vec2 texcoord0;

uniform mat4 transform;

void main() {
    // The '1.0' determines how much of a transformation
    // is applied as translation.
    // Setting it to 0 would mean no translation is done.
    gl_Position = transform * vec4(position, 1.0);
    texcoord0 = texcoord;
}
