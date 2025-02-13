#include <engine/core.h>

int main(int argc, char* argv[])
{
	log_trace("Hello %s", "world");
	log_debug("Hello %s", "world");
	log_info ("Hello %s", "world");
	log_warn ("Hello %s", "world");
	log_error("Hello %s", "world");
	log_fatal("Hello %s", "world");

	// Creates Window
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        log_error("Failed to init SDL3");

    log_debug("SDL3 init successful");

    pWindow = SDL_CreateWindow((const char*)"Jumpio",
        640, 480, SDL_WINDOW_OPENGL);


    if (!pWindow)
    {
        log_error("Failed to create a SDL window!");
    }

    log_debug("Window created");

    SDL_ShowWindow(pWindow);

    SDL_ShowCursor();

    // Init OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    glContext = SDL_GL_CreateContext(pWindow);

    if (glContext == NULL)
    {
        printf("Failed to create an OpenGL context!\n");
        return -1;
    }

    SDL_GL_MakeCurrent(pWindow, glContext);

    if (gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) < 0)
    {
        printf("Failed to load OpenGL library!\n");
        return -1;
    }

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(pWindow);

    SDL_Delay(4000);

	return 0;
}