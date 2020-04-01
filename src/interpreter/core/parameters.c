#include <stdlib.h>
#include "core/parameters.h"

void free_parameter(ParameterType type, ParameterValue value)
{
    if (is_parameter_literal(type) &&
        value.literal != NULL)
    {
      free(value.literal);
      value.literal = NULL;
    }
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