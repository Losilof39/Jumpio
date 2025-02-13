#include <engine/core.h>
#include "application/app.h"

//extern R2DStorage s_Data;

static Application app;

int main(int argc, char* argv[])
{
    app.title = "Jumpio";
    app.version = "0.0.1";

    Application_Init(&app);

    Application_Run(&app);

    Application_Cleanup(&app);

    // Init OpenGL

    vec3 color = { 0.0, 1.0, 0.0 };
    vec3 pos = { 100, 0, 0 };
    vec3 size = { 200, 200, 0 };

    log_debug("Initializing OpenGL 4.6 ...");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    app.glContext = SDL_GL_CreateContext(app.pWindow);

    if (app.glContext == NULL)
    {
        printf("Failed to create an OpenGL context!\n");
        return -1;
    }

    SDL_GL_MakeCurrent(app.pWindow, app.glContext);

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

    SDL_GL_SwapWindow(app.pWindow);

    SDL_Delay(1000);

	return 0;
}