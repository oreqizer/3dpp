#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

#include "camera.h"
#include "transform.h"

static std::string LoadShader(const std::string& filename);
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& msg);
static GLuint CreateShader(const std::string& text, GLenum type);

class Shader {
public:
    Shader(const std::string& filevert, const std::string& filefrag);
    virtual ~Shader();

    void Bind();
    void Update(const Transform& transform, const Camera& camera);
protected:
private:
    static const unsigned int NUM_SHADERS = 2;

    enum {
        TRANSFORM_U,

        NUM_UNIFORMS
    };

    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];
    GLuint m_uniforms[NUM_UNIFORMS];
};

#endif // SHADER_H
