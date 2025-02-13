#include <engine/core.h>

extern R2DStorage s_Data;

int main(int argc, char* argv[])
{
    vec3 color = {0.0, 1.0, 0.0};
    vec3 pos = { 0 };
    vec3 size = { 200, 200, 0};

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

    log_debug("Initializing OpenGL 4.6 ...");
    // Init OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

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

    log_debug("OpenGL 4.6 context created successfully");

    // enable OpenGL 4.6 debug features
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(MessageCallback, 0);

    log_debug("Debug Output feature is enabled");

    log_debug("Inititializing sprite renderer");
    InitRenderer2D();

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    R2D_DrawColoredQuad(pos, size, color);

    SDL_GL_SwapWindow(pWindow);

    SDL_Delay(1000);

	return 0;
}