#include <string.h>
#include <stdlib.h>
#include "run/run_instruction_branching.h"
#include "platforms/logging.h"
#include "core/array.h"
#include "errors.h"

/**
 * Implement -> LABEL instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_jump_label(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    int target_label = parameters->first.identifier;
    bool instruction_ok = jump_to_label(program, instruction_pointer, target_label);
    return instruction_ok;
}

/**
 * Implement -> BANK instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_jump_bank(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    bool found_label = false;
    Bank *bank = get_bank_from_parameter(program, &(parameters->first));

    if (bank != NULL)
    {
        int target_label = get_bank_as_integer(bank);
        found_label = jump_to_label(program, instruction_pointer, target_label);
    }
    else
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_BANK_UNDEFINED, 
            "jump", parameters->first.identifier);
        increment_instruction(instruction_pointer);
    }
    
    return found_label;
}

/**
 * Implement IF= instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_if_equal(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    log_debug("Comparing parameters for equality.\n");
    bool is_equal = is_parameters_equal(program, parameters);

    // If is equal, run the next instruction. Otherwise skip it.
    if (is_equal) 
    {
        increment_instruction(instruction_pointer);
    }
    else
    {
        skip_next_instruction(instruction_pointer);
    }

    return true;
}

/**
 * Implement IF! instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_if_not_equal(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    log_debug("Comparing parameters for inequality.\n");
    bool is_equal = is_parameters_equal(program, parameters);

    // If is not equal, run the next instruction. Otherwise skip it.
    if (!is_equal) 
    {
        increment_instruction(instruction_pointer);
    }
    else
    {
        skip_next_instruction(instruction_pointer);
    }

    return true;
}

/**
 * Implement IF> instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_if_greater_than(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
    log_debug("Comparing parameters for greater than.\n");
    Bank *first_bank = get_bank_from_parameter(program, &(parameters->first));
    Bank *second_bank = get_bank_from_parameter(program, &(parameters->second));
    bool is_greater = false;

    if (first_bank != NULL && second_bank != NULL)
    {
        BankType type = first_bank->type;
        if (type == TYPE_INTEGER)
        {
            is_greater = 
                get_bank_as_integer(first_bank) >
                get_bank_as_integer(second_bank);
        }
        else if (type == TYPE_FLOAT)
        {
            is_greater = 
                get_bank_as_float(first_bank) >
                get_bank_as_float(second_bank);
        }
        else
        {
            is_greater = false;
        }
    }
    else
    {
        is_greater = false;
    }
    
    // If is not equal, run the next instruction. Otherwise skip it.
    if (is_greater) 
    {
        increment_instruction(instruction_pointer);
    }
    else
    {
        skip_next_instruction(instruction_pointer);
    }

    return true;
}

/**
 * Implement IF< instruction.
 * 
 * @param program the snowflake program.
 * @param parameters the parameters for the instruction.
 * @param instruction_pointer the current instruction pointer for the program.
 * @return whether the instruction executed successfully.
 */
bool instruction_if_lesser_than(Program *program, Parameters *parameters, InstructionPointer *instruction_pointer)
{
     log_debug("Comparing parameters for lesser than.\n");
    Bank *first_bank = get_bank_from_parameter(program, &(parameters->first));
    Bank *second_bank = get_bank_from_parameter(program, &(parameters->second));
    bool is_lesser = false;

    if (first_bank != NULL && second_bank != NULL)
    {
        BankType type = first_bank->type;
        if (type == TYPE_INTEGER)
        {
            is_lesser = 
                get_bank_as_integer(first_bank) <
                get_bank_as_integer(second_bank);
        }
        else if (type == TYPE_FLOAT)
        {
            is_lesser = 
                get_bank_as_float(first_bank) <
                get_bank_as_float(second_bank);
        }
        else
        {
            is_lesser = false;
        }
    }
    else
    {
        is_lesser = false;
    }
    
    // If is not equal, run the next instruction. Otherwise skip it.
    if (is_lesser) 
    {
        increment_instruction(instruction_pointer);
    }
    else
    {
        skip_next_instruction(instruction_pointer);
    }

    return true;
}

/**
 * Whether the two parameters are equal.
 * 
 * @param program the program.
 * @param parameters the parameters to compare.
 * @return whether the parameters are equal.
 */
bool is_parameters_equal(Program *program, Parameters *parameters)
{
    Bank *first_bank = get_bank_from_parameter(program, &(parameters->first));
    Bank *second_bank = get_bank_from_parameter(program, &(parameters->second));
    
    bool is_equal = false;

    if (first_bank == NULL && second_bank == NULL)
    {
        is_equal = true;
    }
    if (first_bank != NULL && second_bank != NULL)
    {
        BankType type = first_bank->type;

        if (type == TYPE_BOOLEAN)
        {
            is_equal = 
                get_bank_as_boolean(first_bank) ==
                get_bank_as_boolean(second_bank);
        }
        else if (type == TYPE_INTEGER)
        {
            is_equal = 
                get_bank_as_integer(first_bank) ==
                get_bank_as_integer(second_bank);
        }
        else if (type == TYPE_FLOAT)
        {
            is_equal = 
                get_bank_as_float(first_bank) ==
                get_bank_as_float(second_bank);
        }
        else if (type == TYPE_STRING)
        {
            is_equal = is_string_equal(first_bank, second_bank);
        }
        else if (type == TYPE_ARRAY)
        {
            is_equal = false;
        }
    }
    else
    {
        is_equal = false;
    }

    return is_equal;
}

/**
 * Whether the two strings are equal.
 * 
 * @param first_bank the bank containing the first string.
 * @param second_bank the bank containing the second string.
 * @return whether the strings are equal.
 */
bool is_string_equal(Bank *first_bank, Bank *second_bank)
{
    // Get the strings.
    char *first_string = get_bank_as_string(first_bank);
    char *second_string = get_bank_as_string(second_bank);
    bool is_equal = false;

    // Compare the strings.
    if (first_string != NULL && second_string != NULL)
    {
        log_debug("Comparing '%s' with '%s'\n.", first_string, second_string);
        is_equal = strcmp(first_string, second_string) == 0;
    }
    else if (first_string == NULL && second_string == NULL)
    {
        is_equal = true;
    }
    else
    {
        is_equal = false;
    }
    
    // Free the strings and return the findings.
    if (first_string != NULL) free(first_string);
    if (second_string != NULL) free(second_string);
    return is_equal;
}

/**
 * Jump to the instruction pointer associated with a label.
 * 
 * @param program the program containing the label.
 * @param instruction_pointer the current instruction pointer.
 * @param target_label the label to jump to.
 * @return whether the label was located.
 */
bool jump_to_label(Program *program, InstructionPointer *instruction_pointer, int target_label)
{
    // Find the instruction with the label.
    bool found_instruction_with_label = false;
    InstructionPointer new_instruction_pointer = 
        get_label_instruction_pointer(program, target_label,
            &found_instruction_with_label);
    
    // Found instruction. Jumping to it.
    if (found_instruction_with_label)
    {
        log_debug("Jumping to instruction %02i.\n", new_instruction_pointer + 1);
        go_to_instruction(instruction_pointer, new_instruction_pointer + 1);
        return true;
    }

    // Did not find instruction. Going to next.
    else
    {
        log_error(ERROR_MESG_IGNORING_OPERATION_LABEL_NOT_FOUND, "Jump", target_label);
        increment_instruction(instruction_pointer);
        return false;
    }
}

/**
 * Get the instruction pointer associated with a label.
 * 
 * @param program the program containing the label.
 * @param target_label the label to get the instruction pointer from.
 * @param target_found whether the label was located.
 * @return the instruction pointer to the label.
 */
InstructionPointer get_label_instruction_pointer(Program *program, int target_label, bool *target_found)
{
    // Locate instruction with label.
    for (InstructionPointer index = 0; index < get_instruction_count(program); index++)
    {
        Instruction *instruction = get_instruction(program, index);
        if (instruction->instruction == INSTRUCTION_LABEL &&
            instruction->parameters.first.identifier == target_label)
        {
            *target_found = true;
            return index;
        }
    }

    // Did not find instruction with label.
    *target_found = false;
    return 0;
}
