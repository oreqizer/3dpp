#version 120

attribute vec3 position;
attribute vec2 texcoord;
attribute vec3 normal;

varying vec2 texcoord0;
varying vec3 normal0;

uniform mat4 transform;

void main() {
    // The '1.0' determines how much of a transformation
    // is applied as translation.
    // Setting it to 0 would mean no translation is done.
    gl_Position = transform * vec4(position, 1.0);
    texcoord0 = texcoord;

    // No translations should happen on the normal.
    // Only rotating/scaling is necessary.
    // This only works on uniform meshes!
    normal0 = (transform * vec4(normal, 0.0)).xyz;
}
