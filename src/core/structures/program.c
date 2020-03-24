#include <stdlib.h>
#include <stdio.h>
#include "structures/program.h"
#include "errors.h"
#include "platforms/logging.h"

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

        program->banks = new_array();
        program->banks->free_array_item_function = free_bank;
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
        free_array(program->banks);
        free(program);
    }
}

/* Adds an instruction to the program.
 * @return True if the instruction was added, false if not.
 */
bool append_instruction_to_program(Program *program, Instruction *instruction)
{
    return append_array(program->instructions, instruction);
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
        // Bank index already exists. Delete old. Replace with new.
        Bank *old_bank = (Bank *) remove_array_item(program->banks, bank_index);
        free_bank(old_bank);
        return insert_array_item(program->banks, (ArrayItem *) bank, bank_index);
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
        Bank *bank = (Bank *) remove_array_item(program->banks, bank_index);
        free_bank(bank);
        return true;
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
        return (Bank *) get_array_item(program->banks, index);
    }
    return NULL;
}

/* Gets the index in the banks of the bank with the target identifier. */
BankIndex get_program_bank_index(Program *program, Identifier target_identifier, bool *target_exists)
{
    if (program->banks != NULL)
    {
        for (BankIndex i = 0; i < get_array_count(program->banks); i++)
        {
            Bank *bank = (Bank *) get_array_item(program->banks, i);
            if (bank->identifier == target_identifier) {
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
    return append_array(program->banks, (ArrayItem *) bank);
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

void increment_instruction(InstructionPointer *instruction_pointer)
{
    *instruction_pointer += 1;
}

void skip_next_instruction(InstructionPointer *instruction_pointer)
{
    *instruction_pointer += 2;
}

void go_to_instruction(InstructionPointer *instruction_pointer, InstructionPointer new_location)
{
    *instruction_pointer = new_location;
}