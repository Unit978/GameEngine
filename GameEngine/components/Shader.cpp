#include "Shader.h"

#include <fstream>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;

Shader::Shader(const string& shader_filepath){

    shaderProgramID = glCreateProgram();

    // Obtain the shaders from the the file
    string vertex_shader_code = Shader::loadShaderProgramFile(shader_filepath + ".vs");
    string fragment_shader_code = Shader::loadShaderProgramFile(shader_filepath + ".fs");

    shaders[VERTEX_SHADER] = Shader::createShader(vertex_shader_code, GL_VERTEX_SHADER);
    shaders[FRAGMENT_SHADER] = Shader::createShader(fragment_shader_code, GL_FRAGMENT_SHADER);

    // Attach all the shaders to the program
    for(unsigned i = 0; i < NUM_SHADERS; i++)
        glAttachShader(shaderProgramID, shaders[i]);

    // This needs to be done before linking and validation.
    //glBindAttribLocation(shaderProgramID, 0, "position");
    glBindAttribLocation(shaderProgramID, 1, "tex_coord");
    glBindAttribLocation(shaderProgramID, 2, "normal");

    // Link the compiled shader program to the main application
    glLinkProgram(shaderProgramID);
    Shader::checkErrors(shaderProgramID, GL_LINK_STATUS, true, "Error: Shader program failed to link to main application. ");

    // Check that we have valid shaders
    glValidateProgram(shaderProgramID);
    Shader::checkErrors(shaderProgramID, GL_VALIDATE_STATUS, true, "Error: Shader program is invalid. ");

    // Get access to the uniform variable from the GPU
    // 1st param is the program that the uniform belongs to.
    // 2nd param is the exact name of the uniform variable in the shader program code.
    //uniforms[TRANSFORM_UNI] = glGetUniformLocation(shaderProgramID, "transform");
}

Shader::~Shader(){
    cout << "Destroying shader...\n";

    // Delete each shader individually
    for(unsigned i = 0; i < NUM_SHADERS; i++){

        // detach shader from the program
        glDetachShader(shaderProgramID, shaders[i]);
        glDeleteShader(shaders[i]);
    }

    glDeleteProgram(shaderProgramID);
}

void Shader::bind() const{
    glUseProgram(shaderProgramID);
}

void Shader::update(const Transform& transform, const Camera& camera){

    Matrix4 model_view_projection = camera.getViewProjection() * transform.modelMatrix();

    // Get the address of the first element in the matrix array
    const float* first = &(model_view_projection[0][0]);

    // This is to modify a uniform variable
    // 1st param: the uniform variable (id)
    // 2nd param: how many pieces of data are we going to send in, 1 for a single matrix4
    // 3rd param: boolean, If the matrix needs to be transposed to abide with OpenGL format
    // 4th param: the address of the first element in the matrix
    glUniformMatrix4fv(uniforms[TRANSFORM_UNI], 1, GL_TRUE, first);
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

