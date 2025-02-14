#include <glad/glad.h>
#include "app.h"
#include "engine/input.h"
#include "engine/renderer/renderer2D.h"
#include "engine/log.h"

void Application_Init(Application* app)
{
    // Creates Window
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        log_error("Failed to init SDL3");

    log_debug("SDL3 init successful");

    app->pWindow = SDL_CreateWindow((const char*)app->title,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);


    if ( !(app->pWindow) )
    {
        log_error("Failed to create a SDL window!");
    }

    log_debug("Window created");

    SDL_ShowWindow(app->pWindow);

    SDL_ShowCursor();

    log_debug("Initializing OpenGL 4.6 ...");

    //Memory_Init();
    //Filesystem_Init();
    //Audio_Init();
    Input_Init();
    Renderer2D_Init(app->pWindow);
}

void Application_Menu()
{

}

void Application_Active()
{

}

void Application_Death()
{

}

void Application_Run(Application* app)
{
    SDL_Event ev;

    app->gState = G_MENU;

    while ( (app->gState != G_EXIT) )
    {
        while (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
            case SDL_EVENT_QUIT:
            {
                app->gState = G_EXIT;
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

        switch (app->gState)
        {
        case G_MENU:
        {
            Application_Menu();
        }break;

        case G_ACTIVE:
        {
            Application_Active();
        }break;

        case G_DEATH:
        {
            Application_Death();
        }break;

        default:
            break;
        }
    }
}

void Application_Cleanup(Application* app)
{
    Input_Cleanup();
    Renderer2D_Cleanup();

    SDL_DestroyWindow(app->pWindow);
    SDL_Quit();
}