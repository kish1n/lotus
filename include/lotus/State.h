#pragma once

#include <vector>

class Controller
{
public:
    Controller();

private:
    std::vector<float> m_vertices;
    unsigned int m_VAO;
};

class State
{
public:
    State();

private:
    Controller m_controller;
};