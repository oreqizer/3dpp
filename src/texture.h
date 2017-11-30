#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture {
public:
    Texture(const std::string& filename);
    virtual ~Texture();

    void Bind(unsigned int unit);
protected:
private:
    GLuint m_texture;
};

#endif // TEXTURE_H
