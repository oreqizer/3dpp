#version 120

varying vec2 texcoord0;
varying vec3 normal0;

uniform sampler2D diffuse;

void main() {
    // Lambertian shading
    //
    // The 'lightDirection' is negative to simulate
    // the light reflecting of a surface.
    vec3 lightDirection = vec3(0, 0, 1); // Just hardcoded for now
    gl_FragColor = texture2D(diffuse, texcoord0) * clamp(dot(-lightDirection, normal0), 0.0, 1.0);
}
