#ifndef SNOWFLAKE_PARAMETERS_H
#define SNOWFLAKE_PARAMETERS_H

#include <stdbool.h>

typedef unsigned short Identifier;

typedef enum {
    PARAMETER_NONE = 0,
    PARAMETER_LABEL,
    PARAMETER_BANK,
    PARAMETER_DEVICE,
    PARAMETER_LITERAL,
    PARAMETER_TYPE,
    PARAMETER_OPTIONAL      = 0b1000000,
    PARAMETER_WITHOUT_FLAGS = 0b0111111
} ParameterType;

typedef union {
    Identifier identifier;
    char *literal;
} ParameterValue;

void free_parameter(ParameterValue *value, ParameterType type);
bool set_parameter_value(ParameterValue *parameter_value, ParameterType parameter_type, char *parameter_string);
bool is_parameter_optional(ParameterType type);
bool is_parameter_none(ParameterType type);
bool is_parameter_literal(ParameterType type);
bool is_parameter_bank(ParameterType type);
bool is_parameter_label(ParameterType type);
bool is_parameter_device(ParameterType type);
bool is_parameter_type(ParameterType type);
ParameterType get_parameter_type_without_flags(ParameterType type);

#endif
