#pragma once

#include <vector>
#include "lotus/GameObject.h"

class State
{
public:
    State() = default;

    std::vector<GameObject*> objs;
};