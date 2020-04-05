#include <stdlib.h>
#include "core/parameters.h"
#include "core/string.h"
#include "core/type_conversion.h"
#include "platforms/logging.h"
#include "errors.h"

/**
 * Frees an instruction parameter.
 * 
 * @param value instruction parameter value.
 * @param type instruction parameter type.
 */
void free_parameter(ParameterValue *value, ParameterType type)
{
    if (is_parameter_literal(type) &&
        value->literal != NULL)
    {
        free(value->literal);
        value->literal = NULL;
    }
}

/**
 * Stores a value in the instruction parameter.
 * 
 * @param parameter_value instruction parameter value.
 * @param parameter_type instruction parameter type.
 * @param parameter_string string to store in the instruction parameter value.
 * @return whether the operation was successful.
 */
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

/**
 * Whether this parameter is a literal.
 * 
 * @param type the type of the parameter.
 * @return whether the parameter is a literal.
 */
bool is_parameter_literal(ParameterType type)
{
    return get_parameter_type_without_flags(type) == PARAMETER_LITERAL;
}

/**
 * Whether this parameter is a bank.
 * 
 * @param type the type of the parameter.
 * @return whether the parameter is a bank.
 */
bool is_parameter_bank(ParameterType type)
{
    return get_parameter_type_without_flags(type) == PARAMETER_BANK;
}

/**
 * Whether this parameter is a label.
 * 
 * @param type the type of the parameter.
 * @return whether the parameter is a label.
 */
bool is_parameter_label(ParameterType type)
{
    return get_parameter_type_without_flags(type) == PARAMETER_LABEL;
}

/**
 * Whether this parameter is a device.
 * 
 * @param type the type of the parameter.
 * @return whether the parameter is a device.
 */
bool is_parameter_device(ParameterType type)
{
    return get_parameter_type_without_flags(type) == PARAMETER_DEVICE;
}

/**
 * Whether this parameter is a type type.
 * 
 * @param type the type of the parameter.
 * @return whether the parameter is a type type.
 */
bool is_parameter_type(ParameterType type)
{
    return get_parameter_type_without_flags(type) == PARAMETER_TYPE;
}

/**
 * Strips any flags OR'd with the type.
 * 
 * @param type the type of the parameter.
 * @return the type of the parameter stripped of any flags.
 */
ParameterType get_parameter_type_without_flags(ParameterType type)
{
    return (type & PARAMETER_WITHOUT_FLAGS);
}

/**
 * Whether this parameter type has the OPTIONAL flag.
 * 
 * @param type the type of the parameter.
 * @return whether the parameter has the OPTIONAL flag.
 */
bool is_parameter_optional(ParameterType type)
{
    return ((type & PARAMETER_OPTIONAL) == PARAMETER_OPTIONAL);
}

/**
 * Whether this parameter is supposed to have no value.
 * 
 * @param type the type of the parameter.
 * @return whether this parameter is supposed to have no value.
 */
bool is_parameter_none(ParameterType type)
{
    return (type == PARAMETER_NONE);
}