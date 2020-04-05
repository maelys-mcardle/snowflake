#include <stdlib.h>
#include "platforms/logging.h"
#include "core/array.h"
#include "errors.h"
#include "run/run_instruction_array.h"

/**
 * Implement +[] instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_bank_to_first(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    bool instruction_ok = bank_to_array(program, parameters, FIRST);
    increment_instruction(instruction_pointer);
    return instruction_ok;
}

/**
 * Implement []+ instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_bank_to_last(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    bool instruction_ok = bank_to_array(program, parameters, LAST);
    increment_instruction(instruction_pointer);
    return instruction_ok;
}

/**
 * Implement -[] instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_first_to_bank(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    bool instruction_ok = array_to_bank(program, parameters, FIRST);
    increment_instruction(instruction_pointer);
    return instruction_ok;
}

/**
 * Implement []- instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_last_to_bank(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    bool instruction_ok = array_to_bank(program, parameters, LAST);
    increment_instruction(instruction_pointer);
    return instruction_ok;
}

/**
 * Implement >[] instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_first_to_index(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    bool instruction_ok = array_shift_positions(program, parameters, FIRST, INDEX);
    increment_instruction(instruction_pointer);
    return instruction_ok;
}

/**
 * Implement []< instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_last_to_index(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    bool instruction_ok = array_shift_positions(program, parameters, LAST, INDEX);
    increment_instruction(instruction_pointer);
    return instruction_ok;
}

/**
 * Implement [<] instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_index_to_first(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    bool instruction_ok = array_shift_positions(program, parameters, INDEX, FIRST);
    increment_instruction(instruction_pointer);
    return instruction_ok;
}

/**
 * Implement [>] instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_index_to_last(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    bool instruction_ok = array_shift_positions(program, parameters, INDEX, LAST);
    increment_instruction(instruction_pointer);
    return instruction_ok;
}

/**
 * Inserts bank in the array.
 * 
 * @param program snowflake program.
 * @param parameters parameters for the instruction that invoked this.
 * @param position position in the array to insert the bank to.
 * @return whether the operation was successful.
 */
bool bank_to_array(Program *program, Parameters *parameters, ArrayPosition position)
{
    Bank *array_parameter = get_bank_from_parameter(program, &(parameters->first));
    Bank *bank_parameter = get_bank_from_parameter(program, &(parameters->second));
    bool instruction_ok = false;

    // Only do the action if the bank and array are defined.
    if (array_parameter == NULL)
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_NOT_ARRAY,
            "bank insertion to array", parameters->first.identifier);
        return false;
    }

    if (bank_parameter == NULL)
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_UNDEFINED,
            "bank insertion to array", parameters->first.identifier);
        return false;
    }
        
    log_debug("Moving Bank %02i to %s item of array in Bank %02i.\n",
        bank_parameter->identifier, 
        position == FIRST ? "first" : "last",
        array_parameter->identifier);

    // Get the array.
    bool read_array_ok = false;
    Array *array = get_bank_array(array_parameter, &read_array_ok);

    if (!read_array_ok)
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_NOT_ARRAY,
            "bank insertion to array", array_parameter->identifier);
        return false;
    }

    // Add the bank to the array.
    bool operation_ok = 
        (position == FIRST) ? 
            prepend_array(array, (ArrayItem *) bank_parameter):
            append_array(array, (ArrayItem *) bank_parameter);

    // Clear the bank from the main program memory, now that it's in
    // the array.
    if (operation_ok)
    {
        instruction_ok = 
            remove_program_bank_without_freeing(
                program, bank_parameter->identifier);
    }

    return instruction_ok;
}

/**
 * Retrieves bank in the array.
 * 
 * @param program snowflake program.
 * @param parameters parameters for the instruction that invoked this.
 * @param position position in the array to retrieve the bank from.
 * @return whether the operation was successful.
 */
bool array_to_bank(Program *program, Parameters *parameters, ArrayPosition position)
{
    // Get the bank containing the array.
    Bank *array_parameter = get_bank_from_parameter(program, &(parameters->first));
    if (array_parameter == NULL)
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_NOT_ARRAY,
            "array item to bank", parameters->first.identifier);
        return false;
    }

    // Get the array from the bank.
    bool read_array_ok = false;
    Array *array = get_bank_array(array_parameter, &read_array_ok);
    if (!read_array_ok)
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_NOT_ARRAY,
            "array item to bank", array_parameter->identifier);
        return false;
    }

    // Make sure the array contains values.
    if (get_array_count(array) == 0)
    {
        log_debug("Bank %02i array is empty; aborting.\n",
            array_parameter->identifier);
        return false;
    }

    // Get the identifier for the bank.
    Identifier bank_identifier = parameters->second.identifier;

    log_debug("Moving %s item of array in Bank %02i into Bank %02i.\n",
        position == FIRST ? "first" : "last",
        array_parameter->identifier,
        bank_identifier);

    // Get the item from the array.
    Bank *bank =
        (position == FIRST) ?
            (Bank *) remove_array_first(array):
            (Bank *) remove_array_last(array);

    // A check was already made to make sure that the array wasn't empty.
    // If no items was returned, then something is going wrong. Maybe
    // out of memory.
    if (bank == NULL)
    {
        log_error(ERROR_MESG_UNEXPECTED_NULL_VALUE);
        return false;
    }

    // The identifier on the bank retrieved from the array will be
    // out of date. Change it to the new one.
    bank->identifier = bank_identifier;

    // Insert bank into program.
    bool set_bank_ok = set_program_bank(program, bank);

    return set_bank_ok;
}

/**
 * Shift the position of a bank in the array.
 * 
 * @param program snowflake program.
 * @param parameters parameters for the instruction that invoked this.
 * @param from position in the array that contains the bank.
 * @param to position in the array to move the bank to.
 * @return whether the operation was successful.
 */
bool array_shift_positions(Program *program, Parameters *parameters, ArrayPosition from, ArrayPosition to)
{
    Bank *array_parameter = get_bank_from_parameter(program, &(parameters->first));
    Bank *bank_parameter = get_bank_from_parameter(program, &(parameters->second));

    // Only do the action if the bank and array are defined.
    if (array_parameter == NULL)
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_NOT_ARRAY,
            "array shift item", parameters->first.identifier);
        return false;
    }

    if (bank_parameter == NULL)
    {
         log_error(ERROR_MESG_IGNORING_OPERATION_BANK_UNDEFINED,
            "array shift item", parameters->second.identifier);
        return false;
    }
        
    log_debug("Moving Bank %02i item %s to %s.\n",
        bank_parameter->identifier, 
        from == FIRST ? "first" : ((from == LAST) ? "last" : "index"),
        to == FIRST ? "first" : ((to == LAST) ? "last" : "index"));

    // Get the array from the bank.
    bool read_array_ok = false;
    Array *array = get_bank_array(array_parameter, &read_array_ok);
    if (!read_array_ok)
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_NOT_ARRAY,
            "array shift item", array_parameter->identifier);
        return false;
    }
    ArrayIndex index_in_bank = get_bank_as_integer(bank_parameter);
    ArrayIndex from_index = get_array_index_from_position(array, from, index_in_bank);
    ArrayIndex to_index = get_array_index_from_position(array, to, index_in_bank);

    bool move_ok = false;
    ArrayItem *item = remove_array_item(array, from_index);
    if (item != NULL)
    {
        move_ok = insert_array_item(array, item, to_index);
    }
    
    return move_ok;
}

/**
 * Translates a named position (eg. first, last, index) into a numeric index.
 * 
 * @param array the array to get the index from.
 * @param position named position.
 * @param index the numeric index when the named position is INDEX.
 * @return the numeric index for the named position.
 */
ArrayIndex get_array_index_from_position(Array *array, ArrayPosition position, ArrayIndex index)
{
    ArrayCount array_size;
    switch (position)
    {
        case FIRST:
            return 0;
        case LAST:
            array_size = get_array_count(array);
            return array_size > 0 ? array_size - 1 : 0;
        case INDEX:
            return index;
        default:
            return 0;
    }
}
