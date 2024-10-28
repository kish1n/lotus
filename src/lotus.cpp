#include "SDL3/SDL.h"

#include <iostream>

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 480;

using namespace std;

int main(int argc, char** args)
{
    cout << "hi" << endl;
    SDL_Log("main():\n");
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        //Create window
        window = SDL_CreateWindow( "SDL Tutorial", SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        if (window == NULL)
        {
            SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            //Get window surface
			screenSurface = SDL_GetWindowSurface(window);

			//Fill the surface white
			SDL_FillSurfaceRect(screenSurface, nullptr, SDL_MapSurfaceRGB(screenSurface, 0, 0, 0xFF));
			
			//Update the surface
			SDL_UpdateWindowSurface(window);

			//Hack to get window to stay up
			SDL_Event e;
            bool quit = false;
            while (!quit)
            {
                while(SDL_PollEvent(&e))
                {
                    if (e.type == SDL_EVENT_QUIT)
                        quit = true;
                }
            }
        }
    }

    //Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();
    
    return 0;
}