#include "engine/common.h"
#include <stdarg.h>
#include <stdio.h>

char* FormatText(const char* text, ...)
{
    static char buffer[256];
    va_list args;
    va_start(args, text);

    vsprintf(buffer, text, args);
    va_end(args);
    return buffer;
}