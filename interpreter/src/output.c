#include <stdbool.h>
#include "headers/output.h"

bool debug_mode = false;

void enable_debug_mode()
{
    debug_mode = true;
}

void log_debug(const char * format, ... )
{
    if (debug_mode) {
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
