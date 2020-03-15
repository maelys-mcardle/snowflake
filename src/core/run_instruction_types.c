#include <stdlib.h>
#include <string.h>
#include "headers/run_instruction_types.h"
#include "headers/logging.h"
#include "headers/type_conversion.h"
#include "headers/bank.h"
#include "headers/errors.h"
#include "headers/string.h"

/* Stores a variable in a bank; type is inferred.
 * VAR BANK LITERAL 
 */
bool instruction_variable(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    char *literal = parameters->second.literal;

    if (is_float(literal) && has_period(literal))
    {
        return instruction_float(program, parameters, instruction_pointer);
    }
    else if (is_integer(literal))
    {
        return instruction_integer(program, parameters, instruction_pointer);
    }
    else
    {
        return instruction_string(program, parameters, instruction_pointer);
    }
}

/* Stores a boolean in a bank.
 * BLN BANK LITERAL 
 */
bool instruction_boolean(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    bool is_boolean;

    // Convert literal to boolean.
    char *boolean_string = parameters->second.literal;
    int boolean_value = string_to_boolean(boolean_string, &is_boolean);

    // Boolean is valid.
    if (is_boolean)
    {
        // Create a bank if it doesn't exist.
        Bank *bank = get_or_new_bank_from_parameter(program, &(parameters->first));

        // Set the boolean for the bank.
        if (bank != NULL && 
            set_bank_boolean(bank, boolean_value))
        {   
            log_debug("Set bank %02i as boolean value %s\n", 
                bank->identifier, boolean_value ? "true" : "false");
        }
    }
    else
    {
        log_error(ERROR_MESG_LITERAL_IS_NOT_BOOLEAN, boolean_string);
    }
    
    *instruction_pointer += 1;
    return is_boolean;
}

/* Stores an integer in a bank.
 * INT BANK LITERAL 
 */
bool instruction_integer(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    bool is_integer;

    // Convert literal to integer.
    char *integer_string = parameters->second.literal;
    int integer_value = string_to_integer(integer_string, &is_integer);

    // Integer is valid.
    if (is_integer)
    {
        // Create a bank if it doesn't exist.
        Bank *bank = get_or_new_bank_from_parameter(program, &(parameters->first));

        // Set the integer for the bank.
        if (bank != NULL && 
            set_bank_integer(bank, integer_value))
        {   
            log_debug("Set bank %02i as integer value %i\n", 
                bank->identifier, integer_value);
        }
    }
    else
    {
        log_error(ERROR_MESG_LITERAL_IS_NOT_INTEGER, integer_string);
    }
    
    *instruction_pointer += 1;
    return is_integer;
}

/* Stores a float in a bank.
 * FLT BANK LITERAL 
 */
bool instruction_float(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    bool is_float;

    // Convert literal to float.
    char *float_string = parameters->second.literal;
    float float_value = string_to_float(float_string, &is_float);

    // Float is valid.
    if (is_float)
    {
        // Create a bank if it doesn't exist.
        Bank *bank = get_or_new_bank_from_parameter(program, &(parameters->first));

        // Set the float for the bank.
        if (bank != NULL && 
            set_bank_float(bank, float_value))
        {   
            log_debug("Set bank %02i as float value %f\n", 
                bank->identifier, float_value);
        }
    }
    else
    {
        log_error(ERROR_MESG_LITERAL_IS_NOT_FLOAT, float_value);
    }
    
    *instruction_pointer += 1;
    return is_float;
}

/* Stores a string in a bank.
 * STR BANK LITERAL 
 */
bool instruction_string(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    char *string = parameters->second.literal;

    // Create a bank if it doesn't exist.
    Bank *bank = get_or_new_bank_from_parameter(program, &(parameters->first));

    // Set the strubg for the bank.
    if (bank != NULL && 
        set_bank_string(bank, string))
    {   
        log_debug("Set bank %02i as string value '%s'\n", 
            bank->identifier, string);
    }

    *instruction_pointer += 1;
    return true;
}

bool instruction_array(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    // Create a bank if it doesn't exist.
    Bank *bank = get_or_new_bank_from_parameter(program, &(parameters->first));

    // Set the strubg for the bank.
    if (bank != NULL && 
        set_empty_bank_array(bank))
    {
        log_debug("Set bank %02i as empty array\n", 
            bank->identifier);
    }

    *instruction_pointer += 1;
    return true;
}