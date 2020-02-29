#include <stdlib.h>
#include <string.h>
#include "headers/run_instruction_types.h"
#include "headers/output.h"
#include "headers/type_conversion.h"
#include "headers/bank.h"
#include "headers/errors.h"

/* Stores a variable in a bank; type is inferred.
 * VAR BANK LITERAL 
 */
bool instruction_variable(Program *program, Instruction *instruction, int *instruction_pointer)
{
    char *literal = instruction->parameters.second.string;

    if (is_float(literal) && strchr(literal, '.') != NULL)
    {
        instruction_float(program, instruction, instruction_pointer);
    }
    else if (is_integer(literal))
    {
        instruction_integer(program, instruction, instruction_pointer);
    }
    else
    {
        instruction_string(program, instruction, instruction_pointer);
    }
}

/* Stores a boolean in a bank.
 * BLN BANK LITERAL 
 */
bool instruction_boolean(Program *program, Instruction *instruction, int *instruction_pointer)
{
    bool is_boolean;

    // Convert literal to boolean.
    char *boolean_string = instruction->parameters.second.string;
    int boolean_value = string_to_boolean(boolean_string, &is_boolean);

    // Boolean is valid.
    if (is_boolean)
    {
        // Create a bank.
        Bank *bank = new_bank_from_first_parameter(instruction);

        // Set the boolean for the bank.
        if (bank != NULL && 
            set_bank_boolean(bank, boolean_value))
        {   
            // Append the bank to the program.
            // If it failed, free the memory allocated.
            if (!append_bank_to_program(program, bank))
            {
                free_bank(bank);
            }
            else
            {
                log_debug("Set bank %02i as boolean value %s\n", 
                    bank->identifier, boolean_value ? "true" : "false");
            }
        }
    }
    else
    {
        log_error(ERROR_MESG_LITERAL_IS_NOT_BOOLEAN, boolean_string);
    }
    
    *instruction_pointer += 1;
}

/* Stores an integer in a bank.
 * INT BANK LITERAL 
 */
bool instruction_integer(Program *program, Instruction *instruction, int *instruction_pointer)
{
    bool is_integer;

    // Convert literal to integer.
    char *integer_string = instruction->parameters.second.string;
    int integer_value = string_to_integer(integer_string, &is_integer);

    // Integer is valid.
    if (is_integer)
    {
        // Create a bank.
        Bank *bank = new_bank_from_first_parameter(instruction);

        // Set the integer for the bank.
        if (bank != NULL && 
            set_bank_integer(bank, integer_value))
        {   
            // Append the bank to the program.
            // If it failed, free the memory allocated.
            if (!append_bank_to_program(program, bank))
            {
                free_bank(bank);
            }
            else
            {
                log_debug("Set bank %02i as integer value %i\n", 
                    bank->identifier, integer_value);
            }
        }
    }
    else
    {
        log_error(ERROR_MESG_LITERAL_IS_NOT_INTEGER, integer_string);
    }
    
    *instruction_pointer += 1;
}

/* Stores a float in a bank.
 * FLT BANK LITERAL 
 */
bool instruction_float(Program *program, Instruction *instruction, int *instruction_pointer)
{
    bool is_float;

    // Convert literal to float.
    char *float_string = instruction->parameters.second.string;
    float float_value = string_to_float(float_string, &is_float);

    // Float is valid.
    if (is_float)
    {
        // Create a bank.
        Bank *bank = new_bank_from_first_parameter(instruction);

        // Set the float for the bank.
        if (bank != NULL && 
            set_bank_float(bank, float_value))
        {   
            // Append the bank to the program.
            // If it failed, free the memory allocated.
            if (!append_bank_to_program(program, bank))
            {
                free_bank(bank);
            }
            else
            {
                log_debug("Set bank %02i as float value %f\n", 
                    bank->identifier, float_value);
            }
        }
    }
    else
    {
        log_error(ERROR_MESG_LITERAL_IS_NOT_FLOAT, float_value);
    }
    
    *instruction_pointer += 1;
}

/* Stores a string in a bank.
 * STR BANK LITERAL 
 */
bool instruction_string(Program *program, Instruction *instruction, int *instruction_pointer)
{
    char *string = instruction->parameters.second.string;

    // Create a bank.
    Bank *bank = new_bank_from_first_parameter(instruction);

    // Set the strubg for the bank.
    if (bank != NULL && 
        set_bank_string(bank, string))
    {   
        // Append the bank to the program.
        // If it failed, free the memory allocated.
        if (!append_bank_to_program(program, bank))
        {
            free_bank(bank);
        }
        else
        {
            log_debug("Set bank %02i as string value '%s'\n", 
                bank->identifier, string);
        }
    }

    *instruction_pointer += 1;
}
