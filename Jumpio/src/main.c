#include "engine/core.h"
#include "application/app.h"

int main(int argc, char** argv)
{
    static Application app;

    // CHANGE THIS BACK IF YOU NEED THESE!!
    argc = 0;
    argv = NULL;

    app.title = "Jumpio";
    app.version = "0.0.1";

    Application_Init(&app);

    Application_Run(&app);

    Application_Cleanup(&app);

	return 0;
}