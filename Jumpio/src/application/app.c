#include <glad/glad.h>
#include "app.h"
#include "engine/engine.h"

static Application* appPtr;

void Application_Startup()
{
    // Creates Window
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        log_error("Failed to init SDL3");

    log_info("SDL3 init successful");

    appPtr->pWindow = SDL_CreateWindow((const char*)appPtr->title,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);


    if ( !(appPtr->pWindow) )
    {
        log_error("Failed to create a SDL window!");
    }

    log_info("Window created");

    SDL_ShowWindow(appPtr->pWindow);

    SDL_ShowCursor();

    log_info("Initializing OpenGL 4.6 ...");

    //Memory_Init();
    //Filesystem_Init();
    log_info("Init audio system...");
    Audio_Init();
    log_info("Init input system...");
    Input_Init();
    log_info("Init renderer system...");
    Renderer2D_Init(appPtr->pWindow);
}

void Application_Update()
{
    SDL_Event ev;
    SDL_Time start;
    SDL_Time end;
    f32 delta;

    appPtr->exit = false;

    while ( (!appPtr->exit) )
    {
        start = SDL_GetTicks();

        R2D_StartRendition();

        appPtr->Update();

        while (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
            case SDL_EVENT_QUIT:
            {
                appPtr->exit = true;
            }break;

            case SDL_EVENT_KEY_DOWN:
            case SDL_EVENT_KEY_UP:
            {
                Input_ProcessKey(&ev.key);
            }break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
            case SDL_EVENT_MOUSE_BUTTON_UP:
            {
                Input_ProcessMouseButton(&ev.button);
            }break;

            case SDL_EVENT_MOUSE_MOTION:
            {
                Input_ProcessMouseMotion(&ev.motion);
            }break;

            default:
                break;
            }
        }

        R2D_StopRendition();

        end = SDL_GetTicks();

        delta = (f32)(end - start) / 1000.0f;

        Time_SetDeltaTime(delta);
    }
}

void Application_Cleanup()
{
    appPtr->Cleanup();

    Input_Cleanup();
    Renderer2D_Cleanup();
    Audio_Cleanup();

    SDL_DestroyWindow(appPtr->pWindow);
    SDL_Quit();

    log_info("Engine Shutdown");
}

void Application_Run(Application* app)
{
    appPtr = app;

    Application_Startup();

    appPtr->Init();

    Application_Update();
    Application_Cleanup();
}