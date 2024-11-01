#pragma once

#include "SDL3/SDL.h"

class Drawer
{
public:
    Drawer(int width, int height);
    virtual ~Drawer() = default;

    void draw();
};