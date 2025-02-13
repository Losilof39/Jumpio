#include "app.h"

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
    SDL_Event* ev = NULL;

    app->gState = G_MENU;

    while ( (app->gState != G_EXIT) )
    {
        while (SDL_PollEvent(ev))
        {

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
}