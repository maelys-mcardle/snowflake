#include <stdlib.h>
#include <stdio.h>
#include "headers/program.h"
#include "headers/errors.h"
#include "headers/logging.h"

/* Creates a new program and allocates memory.
 * @return The initialized program.
 */
Program *new_program()
{
    Program *program = (Program *) malloc(sizeof(Program));
    if (program != NULL)
    {
        program->instructions = new_array();
        program->instructions->free_array_item_function = free_instruction;
    }
    else
    {
        log_error(ERROR_MESG_COULD_NOT_ALLOCATE_MEMORY);
    }

    return program;
}

/* Free the allocated data for the program. */
void free_program(Program *program)
{
    if (program != NULL)
    {
        // Free the program.
        free_array(program->instructions);
        free(program);
    }
}

/* Adds an instruction to the program.
 * @return True if the instruction was added, false if not.
 */
bool append_instruction_to_program(Program *program, Instruction *instruction)
{
    return insert_array_last(program->instructions, instruction);
}

bool set_program_bank(Program *program, Bank *bank)
{
    // Get the existing index of the bank, if it's set.
    bool bank_exists = false;
    BankIndex bank_index = get_program_bank_index(program, bank->identifier, &bank_exists);

    if (!bank_exists) 
    {
        // Bank index doesn't exist. Append it.
        return append_bank_to_program(program, bank);
    }
    else
    {
        // Bank index already exists. Replace it.
        free_bank(program->banks.banks[bank_index]);
        program->banks.banks[bank_index] = bank;
        return true;
    }
}

bool remove_program_bank(Program *program, Identifier identifier)
{
    // Get the existing index of the bank, if it's set.
    bool bank_exists = false;
    BankIndex bank_index = get_program_bank_index(program, identifier, &bank_exists);

    if (!bank_exists) 
    {
        // Bank index doesn't exist. Nothing to delete.
        return true;
    }
    else
    {
        // Bank index exists. Delete bank.
        free_bank(program->banks.banks[bank_index]);

        // Shift all the bank indices above down by one.
        int end = program->banks.count;
        for (int remaining_index = bank_index; remaining_index < end - 1; remaining_index++)
        {
            program->banks.banks[remaining_index] = 
                program->banks.banks[remaining_index + 1];
        }

        bool resize_ok = resize_bank_array(program, end - 1);
        return resize_ok;
    }
}

Bank *get_bank_from_parameter(Program *program, ParameterValue *parameter)
{
    Identifier target_identifier = parameter->identifier;
    return get_program_bank(program, target_identifier);
}

Bank *get_program_bank(Program *program, Identifier identifier)
{
    bool bank_exists = false;
    BankIndex index = get_program_bank_index(program, identifier, &bank_exists);
    if (bank_exists) {
        return program->banks.banks[index];
    }
    return NULL;
}

/* Gets the index in the banks of the bank with the target identifier. */
BankIndex get_program_bank_index(Program *program, Identifier target_identifier, bool *target_exists)
{
    if (program->banks.banks != NULL && 
        program->banks.count > 0)
    {
        for (BankIndex i = 0; i < program->banks.count; i++)
        {
            if (program->banks.banks[i]->identifier == target_identifier) {
                *target_exists = true;
                return i;
            }
        }
    }

    *target_exists = false;
    return 0;
}

bool append_bank_to_program(Program *program, Bank *bank)
{
    int new_count = program->banks.count + 1;
    bool resize_ok = resize_bank_array(program, new_count);

    if (resize_ok)
    {
        int last_item = new_count - 1;
        program->banks.banks[last_item] = bank;
    }

    return resize_ok;
}

bool resize_bank_array(Program *program, int new_count)
{
    int new_array_size = sizeof(Bank *) * new_count;
    Bank** new_array = (Bank**) realloc(
        program->banks.banks, 
        new_array_size);

    if (new_array != NULL)
    {
        program->banks.banks = new_array;
        program->banks.count = new_count;
        return true;
    }
    else
    {
        log_error(ERROR_MESG_COULD_NOT_ALLOCATE_MEMORY);
        return false;
    }
}

Bank *new_bank_from_parameter(ParameterValue *parameter)
{
    Identifier identifier = parameter->identifier;
    Bank *bank = new_bank(identifier);
    return bank;
}

Bank *get_or_new_bank_from_parameter(Program *program, ParameterValue *parameter)
{
    Bank *bank = get_bank_from_parameter(program, parameter);
    if (bank == NULL)
    {
        bank = new_bank_from_parameter(parameter);
        if (!append_bank_to_program(program, bank))
        {
            free_bank(bank);
        }
    }

    return bank;
}

Device get_device_from_parameter(Parameters *parameters)
{
    Device device = parameters->first.identifier;
    return device;
}

BankType get_type_from_parameter(Parameters *parameters)
{
    Device device = parameters->first.identifier;
    return device;
}