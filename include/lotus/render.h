#pragma once

#include <memory>

class Shader;

class IDrawer
{
protected:
    IDrawer() = default;

public:
    IDrawer(const IDrawer&) = delete;
    IDrawer& operator=(const IDrawer&) = delete;
    IDrawer(IDrawer&&) = delete;
    IDrawer& operator=(IDrawer&&) = delete;

    virtual ~IDrawer() = default;

    virtual void draw() = 0;
};

class BasicTriangleDrawer final : public IDrawer 
{
public:
    BasicTriangleDrawer(int width, int height);
    ~BasicTriangleDrawer() = default;

    void draw() override;

private:
    unsigned int m_shaderProgram = 0;
    unsigned int m_VAO = 0;
};

class BasicTextureDrawer final : public IDrawer
{
public:
    BasicTextureDrawer(int width, int height);
    ~BasicTextureDrawer() = default;

    void draw() override;
private:
    std::shared_ptr<Shader> m_shader;
    unsigned int m_VAO;
    unsigned int m_texture;
    int width, height;
};
