#include "lotus/State.h"

Controller::Controller()
{
    // default to triangle
    m_vertices = {0.0f, 0.5f, 0.0f, // top
                  -0.5f, 0.f, 0.0f, // top right
                  0.5f, 0.f, 0.0f}; // top right down
}