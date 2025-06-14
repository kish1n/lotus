export module lotus:State;

import std;

class GameObject;

export class State
{
public:
    State() = default;

    std::vector<GameObject*> objs;
};