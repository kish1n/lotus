#include "lotus/programs.h"
#include "lotus/base.h"
#include "glad/glad.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace ShaderProgram
{

const char* defaultVertexShaderPath = "./Content/shaders/basic.vert";
const char* defaultFragmentShaderPath = "./Content/shaders/basic.frag";

unsigned int compileBasicProgram()
{
    return Shader(defaultVertexShaderPath, defaultFragmentShaderPath).getId();
}

unsigned int compileProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
{
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        fatal("Failed to compile shader. Error: %s\n", infoLog);
    }

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        fatal("Failed to compile shader. Error: %s\n", infoLog);
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fatal("Failed to link program. Error: %s\n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

} // namespace ShaderProgram

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexShaderSource;
    std::string fragmentShaderSource;

    std::fstream vertexStream;
    std::fstream fragmentStream;

    std::stringstream vertexBuffer;
    std::stringstream fragmentBuffer;
    
    try
    {
        vertexStream.open(vertexPath, std::ios_base::in);
        vertexBuffer << vertexStream.rdbuf();
        vertexShaderSource = vertexBuffer.str();
        vertexStream.close();

        fragmentStream.open(fragmentPath, std::ios_base::in);
        fragmentBuffer << fragmentStream.rdbuf();
        fragmentShaderSource = fragmentBuffer.str();
        fragmentStream.close();
    }
    catch(const std::exception& e)
    {
        fatal("Failed to open shader files %s, %s", vertexPath, fragmentPath);
    }

    id = ShaderProgram::compileProgram(vertexShaderSource.c_str(), fragmentShaderSource.c_str());
}

void Shader::use()
{
    glUseProgram(id);
}