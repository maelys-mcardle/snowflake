#include "headers/output.h"

void log_debug(const char * format, ... )
{
    if (DEBUG_MODE) {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
}

void log_error(const char * format, ... )
{
    va_list args;
    va_start (args, format);
    vprintf(format, args);
    va_end (args);
}

void print(const char * format, ... )
{
    va_list args;
    va_start (args, format);
    vprintf (format, args);
    va_end (args);
}
