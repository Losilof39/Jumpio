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
	u8 mbUsing;

	void (*Init)();
	void (*Update)();
	void (*Cleanup)();

}Application;

void Application_Startup();
void Application_Run(Application* app);
void Application_Update();
u8 Application_GetHeapSize();
void Application_Cleanup();