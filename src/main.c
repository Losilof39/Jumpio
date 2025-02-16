#include "pong.h"
#include "application/app.h"

int main(int argc, char** argv)
{
    static Application app;

    // CHANGE THIS BACK IF YOU NEED THESE!!
    (int)argc;
    (void*)argv;

    app.title = "Jumpio";
    app.version = "0.0.1";
    app.mbUsing = 1;
    app.Init = Test_Init;
    app.Update = Test_Update;
    app.Cleanup = Test_Cleanup;

    Application_Run(&app);

	return 0;
}