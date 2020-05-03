#ifndef SNOWFLAKE_PARAMETERS_H
#define SNOWFLAKE_PARAMETERS_H

#include <stdbool.h>

typedef unsigned short Identifier;

/**
 * Enum for the parameter types.
 */
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

/**
 * Stores a raw program parameter.
 * 
 * Parameters are either an identifier to a bank/label/etc.
 * Or a literal value, which can then be parsed as a bool/int/string/etc.
 */
typedef union {
    Identifier identifier;
    char *literal;
} ParameterValue;

/**
 * Frees an instruction parameter.
 * 
 * @param value instruction parameter value.
 * @param type instruction parameter type.
 */
void free_parameter(ParameterValue *value, ParameterType type);

/**
 * Stores a value in the instruction parameter.
 * 
 * @param parameter_value instruction parameter value.
 * @param parameter_type instruction parameter type.
 * @param parameter_string string to store in the instruction parameter value.
 * @return whether the parameter value was set.
 */
bool set_parameter_value(ParameterValue *parameter_value, ParameterType parameter_type, char *parameter_string);

/**
 * Whether this parameter type has the OPTIONAL flag.
 * 
 * @param type the type of the parameter.
 * @return whether the parameter has the OPTIONAL flag.
 */
bool is_parameter_optional(ParameterType type);

/**
 * Whether this parameter is supposed to have no value.
 * 
 * @param type the type of the parameter.
 * @return whether this parameter is supposed to have no value.
 */
bool is_parameter_none(ParameterType type);

/**
 * Whether this parameter is a literal.
 * 
 * @param type the type of the parameter.
 * @return whether the parameter is a literal.
 */
bool is_parameter_literal(ParameterType type);

/**
 * Whether this parameter is a bank.
 * 
 * @param type the type of the parameter.
 * @return whether the parameter is a bank.
 */
bool is_parameter_bank(ParameterType type);

/**
 * Whether this parameter is a label.
 * 
 * @param type the type of the parameter.
 * @return whether the parameter is a label.
 */
bool is_parameter_label(ParameterType type);

/**
 * Whether this parameter is a device.
 * 
 * @param type the type of the parameter.
 * @return whether the parameter is a device.
 */
bool is_parameter_device(ParameterType type);

/**
 * Whether this parameter is a type type.
 * 
 * @param type the type of the parameter.
 * @return whether the parameter is a type type.
 */
bool is_parameter_type(ParameterType type);

/**
 * Strips any flags OR'd with the type.
 * 
 * @param type the type of the parameter.
 * @return the type of the parameter stripped of any flags.
 */
ParameterType get_parameter_type_without_flags(ParameterType type);

#endif
