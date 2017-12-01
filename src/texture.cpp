#include <cassert>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"
#include "texture.h"

Texture::Texture(const std::string& filename) {
    int width, height, count;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &count, 4);

    if (data == NULL) {
        std::cerr << "Texture loading failed: " << filename << std::endl;
    }

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    // Controls wrapping in case of an under/overflow:
    //   S - width
    //   T - height
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // When texture is less than resoluiton, it will interpolate linearly
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // When texture is more than resoluiton, it will interpolate linearly
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D,
        0, // Level
        GL_RGBA, // Store format
        width,
        height,
        0, // Border
        GL_RGBA, // Input format, 'stb_image' uses this
        GL_UNSIGNED_BYTE, // Input type
        data
    );

    stbi_image_free(data);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_texture);
}

void Texture::Bind(unsigned int unit) {
    assert(unit >= 0 && unit <= 31);

    // Activates a texture
    // Order is sequential, thus '0 + unit' is OK
    glActiveTexture(GL_TEXTURE0 + unit);

    // All future texture operators are going to use this texture
    glBindTexture(GL_TEXTURE_2D, m_texture);
}
