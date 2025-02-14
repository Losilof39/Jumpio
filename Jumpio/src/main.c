#include "application/app.h"

int main(int argc, char** argv)
{
    static Application app;

    // CHANGE THIS BACK IF YOU NEED THESE!!
    argc = 0;
    argv = NULL;

    app.title = "Jumpio";
    app.version = "0.0.1";

    Application_Run(&app);

	return 0;
}