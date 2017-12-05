#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

static std::string LoadShader(const std::string& filename);
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& msg);
static GLuint CreateShader(const std::string& text, GLenum type);

class Shader {
public:
    Shader(const std::string& filevert, const std::string& filefrag);
    virtual ~Shader();

    void Bind();
protected:
private:
    static const unsigned int NUM_SHADERS = 2;

    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];
};

#endif // SHADER_H
