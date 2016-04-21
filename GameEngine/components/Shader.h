#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <string>
#include <unordered_map>

#include "GL/glew.h"
#include "Transform.h"
#include "Camera.h"

#include "Matrix3.h"
#include "Matrix4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

using std::unordered_map;
using std::string;
using std::cerr;
using std::endl;

class Shader
{
public:

    // Takes in the file path to the shader file program
    Shader(const string&);
    ~Shader();

    // Tell the GPU use this shader
    void bind() const;

    // Update the values of the uniform variables
    //void update(const Transform&, const Camera&);

    template<typename T>
    void setUniformValue(const string& name, const T&);

    GLuint getProgramID() const;

private:

    // A small struct to group together uniform data of the shader.
    struct UniformData{
        UniformData(const string& name, const GLenum type, const GLuint location);
        const string name;
        const GLenum type;
        const GLuint location;
    };

    enum { VERTEX_SHADER, FRAGMENT_SHADER, /*GEOMETRY_SHADER,*/ NUM_SHADERS };

    // The uniform variables to the shader
    enum { TRANSFORM_UNI, NUM_UNIFORMS };

    // shader program handle for OpenGL. This allows access to the program.
    GLuint programID;
    GLuint shaders[NUM_SHADERS];

    // Hold the uniform variables of the shader program
    unordered_map<string, UniformData> uniforms;

    // After the shader has been linked and compiled, the uniforms will be
    // collected and placed into a map for convenience.
    void collectUniforms();

    void setUniform(const UniformData&, const Matrix3&);
    void setUniform(const UniformData&, const Matrix4&);

    void setUniform(const UniformData&, const Vector2&);
    void setUniform(const UniformData&, const Vector3&);
    void setUniform(const UniformData&, const Vector4&);

    void setUniform(const UniformData&, const int&);
    void setUniform(const UniformData&, const float&);

    static void reportUniformTypeError(const UniformData&, const GLenum expectedType);

    // Helper functions to load the shader program from the file
    static string loadShaderProgramFile(const string&);
    static void checkErrors(GLuint, GLuint, bool, const string&);
    static GLuint createShader(const string&, GLenum);
};

template<typename T>
void Shader::setUniformValue(const string& name, const T& value){

    // Check that the uniform exists for the shader.
    const auto itr = uniforms.find(name);
    if (itr == uniforms.end()){
        cerr << "Uniform '" << name << "' does not exist for shader id = " << programID << endl;
        return;
    }

    setUniform(itr->second, value);
}

#endif // SHADER_H
