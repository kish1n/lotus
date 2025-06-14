#pragma once

import std;
#include "lotus/GameObject.h"

class State
{
public:
    State() = default;

    std::vector<GameObject*> objs;
};