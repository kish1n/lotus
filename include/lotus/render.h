#pragma once

#include "SDL3/SDL.h"

class Drawer
{
public:
    Drawer();
    virtual ~Drawer() = default;

    void draw();
};