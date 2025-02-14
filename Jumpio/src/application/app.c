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

    log_debug("Initializing OpenGL 4.6 ...");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    app->glContext = SDL_GL_CreateContext(app->pWindow);

    if (app->glContext == NULL)
    {
        log_error("Failed to create an OpenGL context!\n");
    }

    SDL_GL_MakeCurrent(app->pWindow, app->glContext);

    if (gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress) < 0)
    {
        log_error("Failed to load OpenGL library!\n");
    }

    log_debug("OpenGL 4.6 context created successfully");

    // enable OpenGL 4.6 debug features
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(MessageCallback, 0);

    log_debug("Debug Output feature is enabled");

    Renderer2D_Init();
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
            {

            }break;

            case SDL_EVENT_KEY_UP:
            {

            }break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
            {

            }break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
            {

            }break;

            case SDL_EVENT_MOUSE_MOTION:
            {

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
    SDL_Quit();
    free(app);
}