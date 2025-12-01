#include "lotus/Game.h"
#include "lotus/ResourceManager.h"
#include "lotus/base.h"

#include "SDL3/SDL.h"
#include "glad/glad.h"

#include <format>

void key_callback(SDL_Window *window, const SDL_KeyboardEvent &key_event);
void framebuffer_size_callback(int width, int height);
// The Width of the screen
const unsigned int SCREEN_WIDTH = 800;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 600;

Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char *argv[]) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        fatal(std::format("SDL could not initialize! SDL_Error: {}", SDL_GetError()));
    }

    SDL_Window *window = SDL_CreateWindow("Lotus", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if (!window) {
        fatal(std::format("Window could not be created! SDL_Error: {}", SDL_GetError()));
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetSwapInterval(0);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        fatal(std::format("OpenGL context could not be created! SDL_Error: {}", SDL_GetError()));
    }
    if (!SDL_GL_MakeCurrent(window, glContext)) {
        fatal(std::format("Failed to make current context! SDL_Error: {}", SDL_GetError()));
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        fatal("Failed to initialize GLAD");
    }

    // OpenGL configuration
    // --------------------
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // initialize game
    // ---------------
    Breakout.Init();

    // deltaTime variables
    // -------------------
    float deltaTime = 0.0f;
    Uint64 lastFrame = SDL_GetTicks();
    bool running = true;

    while (running) {
        // calculate delta time
        // --------------------
        Uint64 currentFrame = SDL_GetTicks();
        deltaTime = (currentFrame - lastFrame) / 1000.0f; // Convert to seconds
        lastFrame = currentFrame;

        // poll events
        // -----------
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            } else if (event.type == SDL_EVENT_KEY_DOWN || event.type == SDL_EVENT_KEY_UP) {
                key_callback(window, event.key);
            } else if (event.type == SDL_EVENT_WINDOW_RESIZED) {
                framebuffer_size_callback(event.window.data1, event.window.data2);
            }
        }

        // manage user input
        // -----------------
        Breakout.ProcessInput(deltaTime);

        // update game state
        // -----------------
        Breakout.Update(deltaTime);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Breakout.Render();

        SDL_GL_SwapWindow(window);
    }

    // delete all resources as loaded using the resource manager
    // ---------------------------------------------------------
    ResourceManager::Clear();

    SDL_Quit();
    return 0;
}

void key_callback(SDL_Window *window, const SDL_KeyboardEvent &key_event) {
    // when a user presses the escape key, we destroy the window
    if (key_event.key == SDLK_ESCAPE && key_event.type == SDL_EVENT_KEY_DOWN) {
        SDL_DestroyWindow(window);
        exit(0);
        return;
    }

    SDL_Scancode scancode = key_event.scancode;
    if (key_event.type == SDL_EVENT_KEY_DOWN)
        Breakout.Keys[scancode] = true;
    else if (key_event.type == SDL_EVENT_KEY_UP)
        Breakout.Keys[scancode] = false;
}

void framebuffer_size_callback(int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
