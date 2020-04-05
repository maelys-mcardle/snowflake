#include <stdlib.h>
#include "core/parameters.h"
#include "core/string.h"
#include "core/type_conversion.h"
#include "platforms/logging.h"
#include "errors.h"

void free_parameter(ParameterValue *value, ParameterType type)
{
    if (is_parameter_literal(type) &&
        value->literal != NULL)
    {
        free(value->literal);
        value->literal = NULL;
    }
}

bool store_parameter(ParameterValue *parameter_value, ParameterType parameter_type, char *parameter_string)
{
    // Store the parameter.
    // * Literals are stored as strings.
    // * Banks, devices, labels as integers.
    if (is_parameter_literal(parameter_type))
    {
        // If it's a literal, allocate memory, and copy the string.
        parameter_value->literal = new_string(parameter_string);

        if (parameter_value->literal == NULL)
        {
            log_error(ERROR_MESG_COULD_NOT_ALLOCATE_MEMORY);
            return false;
        }
    }
    else
    {
        // If it's any other value (banks, devices, labels, type) interpret as integer.
        bool parsed_integer_ok;
        parameter_value->identifier = string_to_integer(parameter_string, &parsed_integer_ok);
        
        if (!parsed_integer_ok)
        {
            log_error(ERROR_MESG_COULD_NOT_PARSE_INTEGER, parameter_string);
            return false;
        } 
    }

    return true;
}

bool is_parameter_literal(ParameterType type)
{
    return get_parameter_type_without_flags(type) == PARAMETER_LITERAL;
}

bool is_parameter_bank(ParameterType type)
{
    return get_parameter_type_without_flags(type) == PARAMETER_BANK;
}

bool is_parameter_label(ParameterType type)
{
    return get_parameter_type_without_flags(type) == PARAMETER_LABEL;
}

bool is_parameter_device(ParameterType type)
{
    return get_parameter_type_without_flags(type) == PARAMETER_DEVICE;
}

bool is_parameter_type(ParameterType type)
{
    return get_parameter_type_without_flags(type) == PARAMETER_TYPE;
}

ParameterType get_parameter_type_without_flags(ParameterType type)
{
    return (type & PARAMETER_WITHOUT_FLAGS);
}

bool is_parameter_optional(ParameterType type)
{
    return ((type & PARAMETER_OPTIONAL) == PARAMETER_OPTIONAL);
}

bool is_parameter_none(ParameterType type)
{
    return (type == PARAMETER_NONE);
}