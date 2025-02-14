#pragma once

#include "engine/data_types.h"

typedef struct Application
{
	char* title;
	char* version;
	u8 width;
	u8 height;
	SDL_Window* pWindow;
	b8 exit;

	void (*Init)(void);
	void (*Update)(void);
	void (*Cleanup)(void);

}Application;

void Application_Startup();
void Application_Run(Application* app);
void Application_Update();
void Application_Cleanup();