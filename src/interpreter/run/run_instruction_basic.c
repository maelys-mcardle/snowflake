#include <stdlib.h>
#include <string.h>
#include "run/run_instruction_basic.h"
#include "core/bank.h"
#include "platforms/logging.h"
#include "core/devices.h"
#include "errors.h"
#include "core/array.h"

/**
 * Implement no-op instructions (eg. !!!, ###).
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_noop(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    // Unused parameters. This is done to suppress compiler warnings.
    (void)(program);
    (void)(parameters);

    // Perform no-op.
    bool instruction_ok = true;
    log_debug("No-op instruction.\n");
    increment_instruction(instruction_pointer);
    return instruction_ok;
}

/**
 * Implement DEL instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_delete(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    Bank *bank = get_bank_from_parameter(program, &(parameters->first));
    bool instruction_ok = true;

    if (bank == NULL)
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_UNDEFINED, 
            "deletion", parameters->first.identifier);
    }
    else
    {
        log_debug("Deleting Bank %02i.\n", bank->identifier);
        instruction_ok = remove_program_bank(program, bank->identifier);
    }
    
    increment_instruction(instruction_pointer);
    return instruction_ok;
}

/**
 * Implement TYP instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_type(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    bool instruction_ok = false;

    // Get the banks.
    Bank *bank_to_store_type_in = get_or_new_bank_from_parameter(program, &(parameters->first));
    Bank *bank_with_type_to_get = get_bank_from_parameter(program, &(parameters->second));

    // Bank has a type.
    if (bank_to_store_type_in == NULL)
    {
        log_error(ERROR_MESG_COULD_NOT_ALLOCATE_MEMORY);
        instruction_ok = false;
    }
    else if (bank_with_type_to_get != NULL)
    {
        instruction_ok = set_bank_integer(bank_to_store_type_in, bank_with_type_to_get->type);
    }
    else if (bank_with_type_to_get == NULL)
    {
        instruction_ok = set_bank_integer(bank_to_store_type_in, 0);
    }

    increment_instruction(instruction_pointer);
    return instruction_ok;
}

/**
 * Implement = instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_copy(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    bool instruction_ok = false;

    // Get the banks.
    Bank *bank_destination = get_or_new_bank_from_parameter(program, &(parameters->first));
    Bank *bank_source = get_bank_from_parameter(program, &(parameters->second));

    // Bank has a type.
    if (bank_destination == NULL)
    {
        log_error(ERROR_MESG_COULD_NOT_ALLOCATE_MEMORY);
        instruction_ok = false;
    }
    else if (bank_source != NULL)
    {
        log_debug("Copying to Bank %02i.\n", bank_destination->identifier);
        instruction_ok = copy_bank(bank_destination, bank_source);
    }
    else if (bank_source == NULL)
    {
        log_debug("Source bank is unallocated. Deleting Bank %02i.\n", bank_destination->identifier);
        instruction_ok = remove_program_bank(program, bank_destination->identifier);
    }

    increment_instruction(instruction_pointer);
    return instruction_ok; 
}

/**
 * Implement TO instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_convert(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    bool instruction_ok = false;

    // Get the bank and type to convert to.
    Bank *bank = get_or_new_bank_from_parameter(program, &(parameters->second));
    BankType to_type = get_type_from_parameter(parameters);

    if (bank != NULL)
    {
        log_debug("Converting Bank %02i to type %i.\n", bank->identifier, to_type);
        instruction_ok = convert_bank(bank, to_type);
    }

    increment_instruction(instruction_pointer);
    return instruction_ok;
}

/**
 * Implement LEN instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_length(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    Bank *bank_to_store_length_in = get_or_new_bank_from_parameter(program, &(parameters->first));
    Bank *bank_to_get_length_from = get_bank_from_parameter(program, &(parameters->second));
    bool instruction_ok = false;
    bool parse_ok = true; 

    log_debug("Storing length in Bank %02i.\n",
            bank_to_store_length_in->identifier);

    if (bank_to_get_length_from != NULL &&
        bank_to_get_length_from->type == TYPE_STRING)
    {
        char *string = get_bank_string(bank_to_get_length_from, &parse_ok);
        instruction_ok = 
            set_bank_integer(bank_to_store_length_in, 
                string != NULL ? strlen(string) : 0);
    }
    else if (bank_to_get_length_from != NULL &&
        bank_to_get_length_from->type == TYPE_ARRAY)
    {
        instruction_ok = 
            set_bank_integer(bank_to_store_length_in, 
                get_array_count(
                    get_bank_array(bank_to_get_length_from, &parse_ok)));
    }
    else
    {
        instruction_ok = 
            set_bank_integer(bank_to_store_length_in, 0);
    }

    increment_instruction(instruction_pointer);
    return instruction_ok;
}