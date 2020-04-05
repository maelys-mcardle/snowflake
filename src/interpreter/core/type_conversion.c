#include <errno.h>
#include <stdlib.h>
#include "platforms/logging.h"
#include "core/type_conversion.h"

/**
 * Parses the string as a boolean.
 * String would contain "0" or "1".
 * 
 * @param string string to parse as a boolean.
 * @param ok whether the parsing succeeded.
 * @return the parsed boolean.
 */
bool string_to_boolean(char *string, bool *ok)
{
    // 0: False
    // 1: True
    // Any other value: True
    return string_to_integer(string, ok) != 0;
}

/**
 * Parses the string as an integer.
 * 
 * @param string string to parse as an integer.
 * @param ok whether the parsing succeeded.
 * @return the parsed integer.
 */
int string_to_integer(char *string, bool *ok)
{
    // Catch NULL strings.
    if (string == NULL)
    {
        log_debug("Tried to convert NULL string to integer.\n");
        *ok = false;
        return 0;
    }

    int integer;
    char *end_pointer;
    errno = 0;

    // Parse the string into an integer.
    log_debug("Converting '%s' to integer.\n", string);
    integer = strtol(string,  &end_pointer, 10);

    // Indicate success.
    *ok = (end_pointer != string && errno == 0);

    return integer;
}

/**
 * Parses the string as a float.
 * 
 * @param string string to parse as an float.
 * @param ok whether the parsing succeeded.
 * @return the parsed float.
 */
float string_to_float(char *string, bool *ok)
{
    // Catch NULL strings.
    if (string == NULL)
    {
        log_debug("Tried to convert NULL string to float.\n");
        *ok = false;
        return 0.;
    }

    float floating_point;
    char *end_pointer;
    errno = 0;

    // Parse the string into a float.
    log_debug("Converting '%s' to float.\n", string);
    floating_point = strtof(string,  &end_pointer);

    // Indicate success.
    *ok = (end_pointer != string && errno == 0);

    return floating_point;
}

/**
 * Whether the string can be parsed as a boolean.
 * 
 * @param string string to parse.
 * @return wether the string can be parsed as a boolean.
 */
bool is_boolean(char *string)
{
    bool ok;
    string_to_boolean(string, &ok);
    log_debug("'%s' is %s boolean.\n", string, ok ? "a" : "not a");
    return ok;
}

/**
 * Whether the string can be parsed as a float.
 * 
 * @param string string to parse.
 * @return wether the string can be parsed as a float.
 */
bool is_float(char *string)
{
    bool ok;
    string_to_float(string, &ok);
    log_debug("'%s' is %s float.\n", string, ok ? "a" : "not a");
    return ok;
}

/**
 * Whether the string can be parsed as an integer.
 * 
 * @param string string to parse.
 * @return wether the string can be parsed as an integer.
 */
bool is_integer(char *string)
{
    bool ok;
    string_to_integer(string, &ok);
    log_debug("'%s' is %s integer.\n", string, ok ? "an" : "not an");
    return ok;
}
