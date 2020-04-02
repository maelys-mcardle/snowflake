#include <stdbool.h>
#include <stdlib.h>
#include "platforms/logging.h"

bool debug_mode = false;

void enable_debug_mode()
{
    debug_mode = true;
}

bool is_debug_mode()
{
    return debug_mode;
}

void log_debug(const char * format, ... )
{
    if (debug_mode) {
        va_list args;
        va_start(args, format);
        print_with_va_list(format, args, false);
        va_end(args);
    }
}

void log_error(const char * format, ... )
{
    va_list args;
    va_start (args, format);
    print_with_va_list(format, args, true);
    va_end (args);
}

void print_with_va_list(const char *format, va_list args, bool is_error)
{
    vfprintf(is_error ? stderr : stdout, format, args);
}