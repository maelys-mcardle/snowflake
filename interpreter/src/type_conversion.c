#include <errno.h>
#include <stdlib.h>
#include "headers/type_conversion.h"

bool string_to_boolean(char *string, bool *ok)
{
    // 0: False
    // 1: True
    // Any other value: True
    return string_to_integer(string, ok) != 0;
}

int string_to_integer(char *string, bool *ok)
{
    // Catch NULL strings.
    if (string == NULL)
    {
        *ok = false;
        return 0;
    }

    int integer;
    char *end_pointer;
    errno = 0;

    // Parse the string into an integer.
    integer = strtol(string,  &end_pointer, 10);

    // Indicate success.
    *ok = (end_pointer != string && errno == 0);

    return integer;
}

float string_to_float(char *string, bool *ok)
{
    // Catch NULL strings.
    if (string == NULL)
    {
        *ok = false;
        return 0.;
    }

    float floating_point;
    char *end_pointer;
    errno = 0;

    // Parse the string into an integer.
    floating_point = strtof(string,  &end_pointer);

    // Indicate success.
    *ok = (end_pointer != string && errno == 0);

    return floating_point;
}

bool is_boolean(char *string)
{
    bool ok;
    string_to_boolean(string, &ok);
    return ok;
}

bool is_float(char *string)
{
    bool ok;
    string_to_float(string, &ok);
    return ok;
}

bool is_integer(char *string)
{
    bool ok;
    string_to_integer(string, &ok);
    return ok;
}
