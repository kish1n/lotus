#include <iostream>
#include "SDL3/SDL.h"

int main()
{
    SDL_MemoryBarrierReleaseFunction();
    std::cout << "lotus meow\n";
}