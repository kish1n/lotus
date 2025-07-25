module;
#include "SDL3/SDL.h"
#include "glad/glad.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

module lotus:render.impl;

import std;
import :base;
import :programs;
import :State;
import :render;
import :GameObject;

Drawer::Drawer() {}

BasicTriangleDrawer::BasicTriangleDrawer() {
    std::cout << "BasicTriangleDrawer() - START" << std::endl;

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    const char *vertexShaderPath = "./Content/shaders/basic.vert";
    const char *dynamicFragmentShaderPath = "./Content/shaders/dynamic.frag";

    m_shaderProgram1 = Shader(vertexShaderPath, dynamicFragmentShaderPath).getId();

    std::cout << "BasicTriangleDrawer() - END" << std::endl;
}

void BasicTriangleDrawer::draw(State *state) {
    glClear(GL_COLOR_BUFFER_BIT);

    std::vector<float> vertices;
    vertices.reserve(state->objs.size() * 12); // 4 vertex per gameobject, 3 floats per vertex
    int ptr = 0;
    for (int i = 0; i < state->objs.size(); i++) {
        GameObject &obj = state->objs[i];
        std::vector<float> here = {
            obj.x, obj.y, 0,
            obj.x + obj.width, obj.y, 0,
            obj.x, obj.y + obj.height, 0,
            obj.x + obj.width, obj.y + obj.height, 0};
        vertices.insert(vertices.end(), here.begin(), here.end());
    }
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(decltype(vertices)::value_type),
                 vertices.data(), GL_STATIC_DRAW);

    std::vector<unsigned int> indices;
    for (int i = 0; i < state->objs.size(); i++) {
        GameObject &obj = state->objs[i];
        unsigned int offset = i * 4;
        std::vector<unsigned int> here = {offset,     offset + 1, offset + 2,
                                          offset + 1, offset + 2, offset + 3};
        indices.insert(indices.end(), here.begin(), here.end());
    }

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(decltype(indices)::value_type),
                 indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    int numVertices = state->objs.size() * 6; // 3 for each triangle, 2 triangles per gameobject
    glUseProgram(m_shaderProgram1);
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, (float)SDL_GetTicks() / 1000.0f, glm::vec3(0.0f, 0.0f, 1));

    unsigned int transformLoc = glGetUniformLocation(m_shaderProgram1, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    glDrawElements(GL_TRIANGLES, numVertices, GL_UNSIGNED_INT, 0);

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        fatal(std::format("OpenGL error: {}", err));
    }
}

BasicTextureDrawer::BasicTextureDrawer() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    const char *vertexShader = "./Content/shaders/texture.vert";
    const char *fragmentShader = "./Content/shaders/texture.frag";

    m_shader = std::make_shared<Shader>(vertexShader, fragmentShader);

    float vertices[] = {
        // positions          // colors           // texture coords
        0.75f,  0.75f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top right
        0.75f,  -0.75f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // bottom right
        -0.75f, -0.75f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // bottom left
        -0.75f, 0.75f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f  // top left
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, EBO;
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int textureWidth, textureHeight, nrChannels;
    unsigned char *data =
        stbi_load("Content/lotus.jpg", &textureWidth, &textureHeight, &nrChannels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        fatal("Failed to load texture");
    }

    stbi_image_free(data);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void BasicTextureDrawer::draw(State *state) {
    float x, y;
    Uint32 buttons = SDL_GetMouseState(&x, &y);

    x = 2.f * x / ((float)width) - 1.f;
    y = 1.f - (2.f * y / ((float)height));

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, m_texture);

    m_shader->use();

    int pointLocation = glGetUniformLocation(m_shader->getId(), "ourPoint");
    glUniform2f(pointLocation, x, y);

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
