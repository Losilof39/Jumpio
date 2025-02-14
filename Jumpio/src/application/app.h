#ifndef APP_H
#define	APP_H

#include "engine/core.h"

typedef struct Application
{
	char* title;
	char* version;
	u8 width;
	u8 height;
	SDL_GLContext glContext;
	SDL_Window* pWindow;
	enum GameState gState;
}Application;

enum GameState{ G_MENU = 0, G_ACTIVE, G_DEATH, G_EXIT };

void Application_Init(Application* app);
void Application_Run(Application* app);
void Application_Cleanup(Application* app);
void Application_Menu();
void Application_Active();
void Application_Death();

#endif