#ifndef SHADER_H
#define SHADER_H

#include "GL/glew.h"
#include <string>
#include "Transform.h"
#include "Camera.h"

using std::string;

class Shader
{
public:

    // Takes in the file path to the shader file program
    Shader(const string&);
    ~Shader();

    // Has the GPU use this shader
    void bind() const;

    // Update the values of the uniform variables
    void update(const Transform&, const Camera&);

private:

    enum{ VERTEX_SHADER, FRAGMENT_SHADER, /*GEOMETRY_SHADER, */ NUM_SHADERS };

    // The uniform variables to the shader
    enum{ TRANSFORM_UNI, NUM_UNIFORMS };

    // shader program handle for OpenGL. This allows access to the program.
    GLuint shaderProgramID;
    GLuint shaders[NUM_SHADERS];

    // hold the uniform variables of the shader program
    GLuint uniforms[NUM_UNIFORMS];

    // Helper functions to load the shader program from the file
    static string loadShaderProgramFile(const string&);
    static void checkErrors(GLuint, GLuint, bool, const string&);
    static GLuint createShader(const string&, GLenum);
};

#endif // SHADER_H
