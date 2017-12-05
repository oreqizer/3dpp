#version 120

attribute vec3 position;
attribute vec2 texcoord;

varying vec2 texcoord0;

void main() {
    gl_Position = vec4(position, 1.0);
    texcoord0 = texcoord;
}
