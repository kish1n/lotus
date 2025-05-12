#pragma once

class GameObject
{
public:
    GameObject() = default;
    
    // location from bottom-left (0 to 1)
    float x = 0;
    float y = 0;

    // size of obj (0 to 1)
    float width = 0;
    float height = 0;
};