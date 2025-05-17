#pragma once

class GameObject
{
public:
    GameObject() = default;
    GameObject(float x, float y) 
        : x(x), y(y) {}
    GameObject(float x, float y, float width, float height)
        : x(x), y(y), width(width), height(height) {}
    
    // location from bottom-left (0 to 1)
    float x = -0.1;
    float y = -0.1;

    // size of obj (0 to 1)
    float width = 0.2;
    float height = 0.2;
};