#include <stdio.h>
#include <SDL3/SDL.h>
#include <cglm.h>
#include <log.h>
#include <glad/glad.h>

int main(int argc, char* argv[])
{
    SDL_Window* pWindow;

	log_trace("Hello %s", "world");
	log_debug("Hello %s", "world");
	log_info ("Hello %s", "world");
	log_warn ("Hello %s", "world");
	log_error("Hello %s", "world");
	log_fatal("Hello %s", "world");

	// 
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        log_error("Failed to init SDL3");

    log_debug("SDL3 init successful");

    pWindow = SDL_CreateWindow((const char*)"window_title",
        640, 480, SDL_WINDOW_OPENGL | false);


    if (!pWindow)
    {
        log_error("Failed to create a SDL window!");
    }

    log_debug("Window created");

    SDL_ShowWindow(pWindow);

    SDL_ShowCursor();

    SDL_Delay(4000);

	return 0;
}