#pragma once

namespace ShaderProgram
{

unsigned int compileBasicProgram();

} // namespace ShaderProgram

class Shader
{
public:
    Shader() = delete;
    Shader(const Shader&) = delete;
    Shader& operator=(Shader&) = delete;

    Shader(Shader&&) = default;
    Shader& operator=(Shader&&) = default;

    Shader(const char* vertexPath, const char* fragmentPath);

    void use();

    inline unsigned int getId() { return id; }

private:
    unsigned int id;
};
