#include <stdlib.h>
#include "headers/run_instruction.h"
#include "headers/output.h"
#include "headers/type_conversion.h"
#include "headers/bank.h"
#include "headers/errors.h"

Bank *new_bank_with_identifier(Instruction *instruction)
{
    int identifier = instruction->parameters.first.integer;
    Bank *bank = new_bank(identifier);
    return bank;
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
        Bank *bank = new_bank_with_identifier(instruction);

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