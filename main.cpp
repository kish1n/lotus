#include "SDL3/SDL.h"

#include <iostream>
#include <format>

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

using namespace std;

int main(int argc, char** args)
{
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cerr << format("SDL could not initialize! SDL_Error: {}\n", SDL_GetError());
    }
    else
    {
        /*//Create window
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            cerr << format("Window could not be created! SDL_Error: {}\n", SDL_GetError());
        }*/
    }
}