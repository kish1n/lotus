#pragma once

class Drawer
{
public:
    Drawer(int width, int height);
    virtual ~Drawer() = default;

    void draw();
private:
    unsigned int m_shaderProgram = 0;
    unsigned int m_VAO = 0;
};