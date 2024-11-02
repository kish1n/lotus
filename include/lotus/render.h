#pragma once

class Drawer
{
public:
    Drawer(int width, int height);
    virtual ~Drawer() = default;

    void draw();
};