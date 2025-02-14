#include <engine/core.h>
#include "application/app.h"

//extern R2DStorage s_Data;

int main(int argc, char** argv)
{
    static Application* app;


    // CHANGE THIS BACK IF YOU NEED THESE!!
    argc = 0;
    argv = NULL;

    app = (Application*)malloc(sizeof(Application));
    memset(app, 0, sizeof(app));

    app->title = "Jumpio";
    app->version = "0.0.1";

    Application_Init(app);

    Application_Run(app);

    Application_Cleanup(app);

	return 0;
}