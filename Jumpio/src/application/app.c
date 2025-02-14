#include <glad/glad.h>
#include "app.h"
#include "engine/input.h"
#include "engine/renderer/renderer2D.h"
#include "engine/log.h"

static Application* pGame;

void Application_Init()
{
    // Creates Window
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        log_error("Failed to init SDL3");

    log_debug("SDL3 init successful");

    pGame->pWindow = SDL_CreateWindow((const char*)pGame->title,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL);


    if ( !(pGame->pWindow) )
    {
        log_error("Failed to create a SDL window!");
    }

    log_debug("Window created");

    SDL_ShowWindow(pGame->pWindow);

    SDL_ShowCursor();

    log_debug("Initializing OpenGL 4.6 ...");

    //Memory_Init();
    //Filesystem_Init();
    //Audio_Init();
    Input_Init();
    Renderer2D_Init(pGame->pWindow);
}
vec3 pos = { 0 };

void Application_Menu(f32 delta)
{
    vec2 size = { 100, 100 };
    vec3 col = { 1.0f, 1.0f, 1.0f };

    pos[0] += delta * Input_IsKeyDown(SDL_SCANCODE_D) * 1000.0f;
    pos[1] += delta * Input_IsKeyDown(SDL_SCANCODE_S) * 1000.0f;

    pos[0] -= delta * Input_IsKeyDown(SDL_SCANCODE_A) * 1000.0f;
    pos[1] -= delta * Input_IsKeyDown(SDL_SCANCODE_W) * 1000.0f;

    R2D_DrawColoredQuad(pos, size, col);
}

void Application_Active(f32 delta)
{

}

void Application_Death(f32 delta)
{

}

void Application_Update()
{
    SDL_Event ev;
    SDL_Time start;
    SDL_Time end;
    f32 deltaTime = 0.0f;

    pGame->gState = G_MENU;

    while ( (pGame->gState != G_EXIT) )
    {
        start = SDL_GetTicks();

        R2D_StartRendition();

        switch (pGame->gState)
        {
        case G_MENU:
        {
            Application_Menu(deltaTime);
        }break;

        case G_ACTIVE:
        {
            Application_Active(deltaTime);
        }break;

        case G_DEATH:
        {
            Application_Death(deltaTime);
        }break;

        default:
            break;
        }

        while (SDL_PollEvent(&ev))
        {
            switch (ev.type)
            {
            case SDL_EVENT_QUIT:
            {
                pGame->gState = G_EXIT;
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

        deltaTime = (f32)(end - start) / 1000.0f;
    }
}

void Application_Cleanup()
{
    Input_Cleanup();
    Renderer2D_Cleanup();

    SDL_DestroyWindow(pGame->pWindow);
    SDL_Quit();
}

void Application_Run(Application* app)
{
    pGame = app;

    Application_Init();
    Application_Update();
    Application_Cleanup();
}