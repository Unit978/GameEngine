
#include "Shader.h"
#include "../core/Engine.h"

#include <fstream>
#include <vector>

using std::vector;
using std::ifstream;
using std::cout;

Shader::Shader(const string& shader_filepath){

    programID = glCreateProgram();

    // Obtain the shaders from the the file
    string vertex_shader_code = Shader::loadShaderProgramFile(shader_filepath + ".vs");
    string fragment_shader_code = Shader::loadShaderProgramFile(shader_filepath + ".fs");

    shaders[VERTEX_SHADER] = Shader::createShader(vertex_shader_code, GL_VERTEX_SHADER);
    shaders[FRAGMENT_SHADER] = Shader::createShader(fragment_shader_code, GL_FRAGMENT_SHADER);

    // Attach all the shaders to the program
    for(unsigned i = 0; i < NUM_SHADERS; i++){
        glAttachShader(programID, shaders[i]);
    }

    // This needs to be done before linking and validation.
    glBindAttribLocation(programID, 0, "position");
    glBindAttribLocation(programID, 1, "tex_coord");
    glBindAttribLocation(programID, 2, "normal");

    // Link the compiled shader program to the main application
    glLinkProgram(programID);
    Shader::checkErrors(programID, GL_LINK_STATUS, true, "Error: Shader program failed to link to main application. ");

    // Check that we have valid shaders
    glValidateProgram(programID);
    Shader::checkErrors(programID, GL_VALIDATE_STATUS, true, "Error: Shader program is invalid. ");

    // Get access to the uniform variable from the GPU
    // 1st param is the program that the uniform belongs to.
    // 2nd param is the exact name of the uniform variable in the shader program code.
    //uniforms[TRANSFORM_UNI] = glGetUniformLocation(shaderProgramID, "transform");

    collectUniforms();
}

Shader::~Shader(){
    cout << "Destroying shader...\n";

    // Delete each shader individually
    for(unsigned i = 0; i < NUM_SHADERS; i++){

        // detach shader from the program
        glDetachShader(programID, shaders[i]);
        glDeleteShader(shaders[i]);
    }

    glDeleteProgram(programID);
}

void Shader::bind() const{
    glUseProgram(programID);
}

/*
void Shader::update(const Transform& transform, const Camera& camera){

    Matrix4 model_view_projection = camera.getViewProjection() * transform.modelMatrix();

    // Get the address of the first element in the matrix array
    const float* first = &(model_view_projection[0][0]);

    // This is to modify a uniform variable
    // 1st param: the uniform variable (id)
    // 2nd param: how many pieces of data are we going to send in, 1 for a single matrix4
    // 3rd param: boolean, If the matrix needs to be transposed to abide with OpenGL format
    // 4th param: the address of the first element in the matrix
    glUniformMatrix4fv(uniforms.find("transform")->second.location, 1, GL_TRUE, first);
}*/

void Shader::collectUniforms(){

    vector<GLchar> uniformNameData(256);

    GLint uniformCount;
    glGetObjectParameterivARB(programID, GL_OBJECT_ACTIVE_UNIFORMS_ARB, &uniformCount);

    for (GLint uni = 0; uni < uniformCount; uni++){

        GLint arraySize = 0;
        GLenum type = 0;
        GLsizei actualLength = 0;

        glGetActiveUniform(programID, uni, uniformNameData.size(), &actualLength, &arraySize, &type, &uniformNameData[0]);

        string uniformName(static_cast<char*>(&uniformNameData[0]), actualLength);

        std::pair<string, UniformData> unipair(uniformName, UniformData(uniformName, type, uni));
        uniforms.insert(unipair);
    }
}

void Shader::setUniform(const Shader::UniformData& uniData, const Matrix3& mat){
    if (uniData.type != GL_FLOAT_MAT3){
        reportUniformTypeError(uniData, GL_FLOAT_MAT3);
        return;
    }

    const float* first = &mat.elements[0][0];
    glUniformMatrix3fv(uniData.location, 1, GL_TRUE, first);
}

void Shader::setUniform(const Shader::UniformData& uniData, const Matrix4& mat){
    if  (uniData.type != GL_FLOAT_MAT4){
        reportUniformTypeError(uniData, GL_FLOAT_MAT4);
        return;
    }

    const float* first = &mat.elements[0][0];
    glUniformMatrix4fv(uniData.location, 1, GL_TRUE, first);
}

void Shader::setUniform(const Shader::UniformData& uniData, const Vector2& vec){
    if (uniData.type != GL_FLOAT_VEC2){
        reportUniformTypeError(uniData, GL_FLOAT_VEC2);
        return;
    }

    const float* first = &vec.components[0];
    glUniform2fv(uniData.location, 1, first);
}

void Shader::setUniform(const Shader::UniformData& uniData, const Vector3& vec){
    if (uniData.type != GL_FLOAT_VEC3){
        reportUniformTypeError(uniData, GL_FLOAT_VEC3);
        return;
    }

    const float* first = &vec.components[0];
    glUniform3fv(uniData.location, 1, first);
}

void Shader::setUniform(const Shader::UniformData& uniData, const Vector4& vec){
    if (uniData.type != GL_FLOAT_VEC4){
        reportUniformTypeError(uniData, GL_FLOAT_VEC4);
        return;
    }

    const float* first = &vec.components[0];
    glUniform4fv(uniData.location, 1, first);
}

void Shader::setUniform(const Shader::UniformData& uniData, const int& val){
    if (uniData.type != GL_INT){
        reportUniformTypeError(uniData, GL_INT);
        return;
    }
    glUniform1iv(uniData.location, 1, &val);
}

void Shader::setUniform(const Shader::UniformData& uniData, const float& val){
    if (uniData.type != GL_FLOAT){
        reportUniformTypeError(uniData, GL_FLOAT);
        return;
    }

    glUniform1fv(uniData.location, 1, &val);
}

GLuint Shader::getProgramID() const{
    return programID;
}

// CTOR for the UniformData struct.
Shader::UniformData::UniformData(const string& name, const GLenum type, const GLuint location) :
    name(name), type(type), location(location) {}

void Shader::reportUniformTypeError(const Shader::UniformData& uniData, const GLenum expectedType){

    string uniTypeName;
    Engine::getGlTypeName(uniData.type, uniTypeName);

    string expectedTypeName;
    Engine::getGlTypeName(expectedType, expectedTypeName);

    cerr << "Error. Type mismatch when setting value for uniform '" << uniData.name << '\'' << endl;
    cerr << "\tActual type enum held by uniform: " << uniTypeName << endl;
    cerr << "\tType passed to set the uniform value: " << expectedTypeName << endl;
}


string Shader::loadShaderProgramFile(const string& shader_filepath){

    ifstream file_reader(shader_filepath.c_str());
    string program_code = "";

    if(file_reader.is_open()){
        string program_line;
        while(file_reader.good()){
            getline(file_reader, program_line);
            program_code.append(program_line + '\n');
        }
    }
    else cerr << "Error. Unable to open shader file: " << shader_filepath << endl;

    file_reader.close();
    return program_code;
}

void Shader::checkErrors(GLuint shader_program, GLuint flag, bool isProgram, const string& error_msg){
    GLint success = 0;
    GLchar error[1024] = {0};

    if(isProgram)
        glGetProgramiv(shader_program, flag, &success);
    else
        glGetShaderiv(shader_program, flag, &success);

    if (success == GL_FALSE){
        if(isProgram)
            glGetProgramInfoLog(shader_program, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader_program, sizeof(error), NULL, error);

        cerr << error_msg << ": " << error << endl;
    }
}

// Shader code is the string representation of the shader program obtained from the shader file
GLuint Shader::createShader(const string& shader_code, GLenum shader_type){
    GLuint shader = glCreateShader(shader_type);

    // If shader == 0 then OpenGL failed to create a shader
    if (shader == 0)
        cerr << "Error: Unable to create shader.\n";

    else{
        // c-style array of strings and their corresponding lengths (for each string)
        // In this case, a size of 1 since we are just reading from 1 shader source file
        const GLchar* shader_src_str_array[1];
        GLint shader_src_str_lens[1];

        shader_src_str_array[0] = shader_code.c_str();
        shader_src_str_lens[0] = shader_code.length();

        // 2nd parameters refers to the number of shader sources, in this case we only have 1 source to read from
        glShaderSource(shader, 1, shader_src_str_array, shader_src_str_lens);
        glCompileShader(shader);

        Shader::checkErrors(shader, GL_COMPILE_STATUS, false, "Error: Shader source code failed to compile. ");
    }
    return shader;
}

