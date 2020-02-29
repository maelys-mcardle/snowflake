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
        print_with_va_list(format, args, true);
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

void print_code(const char * format, ... )
{
    va_list args;
    va_start (args, format);
    print_with_va_list(format, args, false);
    va_end (args);
}

void send_to_output(char *string)
{
    printf("%s\n", string);
}

void print_with_va_list(const char *format, va_list args, bool is_error)
{
    vfprintf(is_error ? stderr : stdout, format, args);
}