#include <string>
#include <iostream>
#include <fstream>

#include "shader.h"

Shader::Shader(const std::string& filevert, const std::string& filefrag) {
    m_program = glCreateProgram();

    // Extensions are custom just to distinguish stuff
    m_shaders[0] = CreateShader(LoadShader(filevert), GL_VERTEX_SHADER);
    m_shaders[1] = CreateShader(LoadShader(filefrag), GL_FRAGMENT_SHADER);

    for (GLuint shader : m_shaders) {
        glAttachShader(m_program, shader);
    }

    // Binds values to variables in the shaders
    glBindAttribLocation(m_program, 0, "position");
    glBindAttribLocation(m_program, 1, "texcoord");

    glLinkProgram(m_program);
    CheckShaderError(m_program, GL_LINK_STATUS, true, "Program linking failed");

    glValidateProgram(m_program);
    CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Program is invalid");

    m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
}

Shader::~Shader() {
    for (GLuint shader : m_shaders) {
        glDetachShader(m_program, shader);
        glDeleteShader(shader);
    }

    glDeleteProgram(m_program);
}

void Shader::Bind() {
    glUseProgram(m_program);
}

void Shader::Update(const Transform& transform,  const Camera& camera) {
    glm::mat4 model = camera.GetViewProjection() * transform.GetModel();

    glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

static GLuint CreateShader(const std::string& text, GLenum type) {
    GLuint shader = glCreateShader(type);
    if (shader == 0) {
        std::cerr << "Error: Shader creation failed" << std::endl;
    }

    const GLchar* shaderStrings[1];
    GLint shaderStringsLengths[1];

    shaderStrings[0] = text.c_str();
    shaderStringsLengths[0] = text.length();

    glShaderSource(shader, 1, shaderStrings, shaderStringsLengths);
    glCompileShader(shader);

    CheckShaderError(shader, GL_COMPILE_STATUS, false, "Shader compilation failed");

    return shader;
}

static std::string LoadShader(const std::string& filename) {
    std::ifstream ifs(filename);
    std::string content{
        std::istreambuf_iterator<char>(ifs),
        std::istreambuf_iterator<char>()
    };

    return content;
}

static void CheckShaderError(
    GLuint shader, GLuint flag, bool isProgram, const std::string& msg
) {
    GLint success = 0;
    GLchar error[1024] = {0};

    if (isProgram) {
        glGetProgramiv(shader, flag, &success);
    } else {
        glGetShaderiv(shader, flag, &success);
    }

    if (success == GL_FALSE) {
        if (isProgram) {
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        } else {
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        }

        std::cerr << "Error: " << msg << ": '" << error << "'" << std::endl;
    }
}
